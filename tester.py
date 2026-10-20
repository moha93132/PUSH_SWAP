#!/usr/bin/env python3
"""
push_swap tester — basé sur le sujet v1.2 (4 stratégies, disorder, --bench).

Usage :
    python3 tester.py                         # cherche ./push_swap
    python3 tester.py -p ../push_swap         # chemin du binaire
    python3 tester.py --quick                 # moins d'itérations
    python3 tester.py --runs 50               # nb de tirages pour le benchmark
    python3 tester.py -b ../checker           # teste aussi ton checker (bonus)
    python3 tester.py --only errors,bench     # ne lancer que certaines sections

Sections : errors, format, small, disorder, flags, bench, perf, growth, valgrind, checker
Aucune dépendance (Python 3.8+). Valgrind utilisé s'il est installé.
"""
import argparse
import itertools
import math
import os
import random
import re
import shutil
import subprocess
import sys

OPS = ["sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"]
STRATS = ["--simple", "--medium", "--complex", "--adaptive"]
INT_MIN, INT_MAX = -2**31, 2**31 - 1
TIMEOUT = 15
ERR = "Error\n"

# ───────────────────────────── affichage ─────────────────────────────
USE_COLOR = sys.stdout.isatty()
def c(code, s): return f"\033[{code}m{s}\033[0m" if USE_COLOR else s
GREEN, RED, YEL, BLUE, DIM, BOLD = "32", "31", "33", "36", "2", "1"

class Stats:
    def __init__(self): self.ok = self.ko = self.warn = 0
    def passed(self, msg, verbose=False):
        self.ok += 1
        if verbose: print(f"  {c(GREEN, '✔')} {msg}")
    def failed(self, msg, detail=""):
        self.ko += 1
        print(f"  {c(RED, '✘')} {msg}")
        if detail:
            for line in detail.rstrip().splitlines()[:8]:
                print(f"      {c(DIM, line)}")
    def warned(self, msg):
        self.warn += 1
        print(f"  {c(YEL, '⚠')} {msg}")
    def info(self, msg): print(f"  {c(BLUE, '•')} {msg}")

S = Stats()
def section(title): print(f"\n{c(BOLD, '━━ ' + title + ' ')}{c(DIM, '━' * max(0, 60 - len(title)))}")

# ───────────────────────────── exécution ─────────────────────────────
class Res:
    def __init__(self, rc, out, err, timeout=False):
        self.rc, self.out, self.err, self.timeout = rc, out, err, timeout
    @property
    def crashed(self): return self.rc is not None and self.rc < 0
    def ops(self): return self.out.split("\n")[:-1] if self.out else []

def run(cmd, stdin=None, timeout=TIMEOUT):
    try:
        p = subprocess.run(cmd, input=stdin, capture_output=True, text=True,
                           timeout=timeout, errors="replace")
        return Res(p.returncode, p.stdout, p.stderr)
    except subprocess.TimeoutExpired as e:
        return Res(None, e.stdout or "", e.stderr or "", timeout=True)

def ps(*args, **kw): return run([PUSH_SWAP, *map(str, args)], **kw)

def sig_name(rc):
    try: return f"signal {-rc} ({__import__('signal').Signals(-rc).name})"
    except Exception: return f"signal {-rc}"

# ───────────────────────────── checker interne ─────────────────────────────
def simulate(nums, ops):
    """Renvoie (ok, raison). a[0] = sommet."""
    a, b = list(nums), []
    def sw(s):
        if len(s) > 1: s[0], s[1] = s[1], s[0]
    def ro(s):
        if len(s) > 1: s.append(s.pop(0))
    def rr_(s):
        if len(s) > 1: s.insert(0, s.pop())
    for i, op in enumerate(ops):
        if op == "sa": sw(a)
        elif op == "sb": sw(b)
        elif op == "ss": sw(a); sw(b)
        elif op == "pa":
            if b: a.insert(0, b.pop(0))
        elif op == "pb":
            if a: b.insert(0, a.pop(0))
        elif op == "ra": ro(a)
        elif op == "rb": ro(b)
        elif op == "rr": ro(a); ro(b)
        elif op == "rra": rr_(a)
        elif op == "rrb": rr_(b)
        elif op == "rrr": rr_(a); rr_(b)
        else:
            return False, f"instruction invalide ligne {i + 1} : {op!r}"
    if b: return False, f"stack b non vide ({len(b)} éléments)"
    if a != sorted(nums): return False, "stack a non triée"
    return True, ""

def disorder(nums):
    n = len(nums)
    if n < 2: return 0.0
    inv = 0
    for i in range(n):
        x = nums[i]
        for j in range(i + 1, n):
            if x > nums[j]: inv += 1
    return inv / (n * (n - 1) / 2)

def fmt_args(nums, limit=12):
    s = " ".join(map(str, nums[:limit]))
    return s + (" …" if len(nums) > limit else "")

def check_sort(nums, flags=(), label=None, expect_max=None):
    """Lance push_swap, vérifie le tri. Renvoie le nb d'ops ou None."""
    r = ps(*flags, *nums)
    label = label or f"{' '.join(flags) or '(défaut)'} [{fmt_args(nums)}]"
    if r.timeout: S.failed(f"{label} → TIMEOUT (>{TIMEOUT}s)"); return None
    if r.crashed: S.failed(f"{label} → CRASH {sig_name(r.rc)}"); return None
    if r.err.strip() and "--bench" not in flags:
        S.failed(f"{label} → sortie sur stderr inattendue", r.err); return None
    ok, why = simulate(nums, r.ops())
    if not ok: S.failed(f"{label} → KO : {why}"); return None
    n = len(r.ops())
    if expect_max is not None and n > expect_max:
        S.warned(f"{label} → trié en {n} ops (attendu ≤ {expect_max})")
    else:
        S.passed(label)
    return n

# ───────────────────────────── générateurs ─────────────────────────────
def rand_list(n, lo=-100000, hi=100000):
    return random.sample(range(lo, hi), n)

def with_disorder(n, target, tol=0.02, tries=60):
    """Génère une permutation dont le disorder ≈ target (bruit sur les clés)."""
    base = sorted(rand_list(n))
    reverse = target > 0.5
    t = 1 - target if reverse else target
    lo, hi = 0.0, 4.0 * n
    best = None
    for _ in range(tries):
        s = (lo + hi) / 2
        keys = [(i + random.uniform(0, s), v) for i, v in enumerate(base)]
        arr = [v for _, v in sorted(keys)]
        if reverse: arr.reverse()
        d = disorder(arr)
        if best is None or abs(d - target) < abs(best[0] - target): best = (d, arr)
        if abs(d - target) <= tol: break
        dd = 1 - d if reverse else d
        if dd < t: lo = s
        else: hi = s
    return best[1], best[0]

# ───────────────────────────── sections ─────────────────────────────
def t_errors():
    section("Gestion d'erreurs (\"Error\\n\" sur stderr, rien sur stdout)")
    r = ps()
    if r.crashed: S.failed(f"sans argument → CRASH {sig_name(r.rc)}")
    elif r.out or r.err: S.failed("sans argument → ne doit rien afficher", f"stdout={r.out!r} stderr={r.err!r}")
    else: S.passed("sans argument → rien", True)

    cases = [
        ["0", "one", "2", "3"], ["--adaptive", "0", "one", "2", "3"], ["--simple", "3", "2", "3"],
        ["1", "1"], ["5", "3", "5"], ["0", "-0"], ["1", "+1"], ["0", "00"],
        ["a"], ["1", "2", "a"], ["1a"], ["a1"], ["1-"], ["--1"], ["++1"], ["-"], ["+"],
        ["1.5"], ["1,2"], ["0x10"], ["2147483648"], ["-2147483649"], ["99999999999"],
        ["4294967296"], ["18446744073709551616"], ["-99999999999999999999"],
        ["1", "2147483648"], [""], ["1", ""], ["1", "--unknown", "2"],
        ["--unknown", "1", "2"], ["--complex", "4", "2", "4"],
    ]
    for args in cases:
        r = ps(*args)
        lab = "./push_swap " + " ".join(repr(a) if (a == "" or " " in a) else a for a in args)
        if r.timeout: S.failed(f"{lab} → TIMEOUT"); continue
        if r.crashed: S.failed(f"{lab} → CRASH {sig_name(r.rc)}"); continue
        problems = []
        if r.err != "Error\n": problems.append(f"stderr={r.err!r} (attendu 'Error\\n')")
        if r.out: problems.append(f"stdout non vide : {r.out[:60]!r}")
        if problems: S.failed(lab, "\n".join(problems))
        else: S.passed(lab)

    section("Cas limites valides (doivent trier, pas Error)")
    for args in (["-2147483648", "2147483647"], ["2147483647", "-2147483648", "0"],
                 ["-1", "-2", "-3"], ["0", "-1"], ["42"], ["-2147483648"]):
        check_sort([int(x) for x in args])

    section("Cas ambigus (le sujet ne tranche pas — à défendre en éval)")
    for args, note in ((["+5", "3"], "signe +"), (["007", "3"], "zéros en tête"),
                       (["3 2 1"], "tous les nombres dans un seul argument"),
                       (["3 2", "1"], "argument mixte"), ([" 3", "1"], "espace en tête")):
        r = ps(*args)
        verdict = "Error" if r.err == "Error\n" else ("trie" if not r.crashed and simulate(
            [int(x) for a in args for x in a.split()], r.ops())[0] else "?")
        if r.crashed: S.failed(f"{args} ({note}) → CRASH {sig_name(r.rc)}")
        else: S.info(f"{args!s:<22} {c(DIM, note):<40} → {verdict}")

def t_format():
    section("Format de sortie")
    nums = rand_list(50)
    for fl in ([], *[[s] for s in STRATS]):
        r = ps(*fl, *nums)
        lab = " ".join(fl) or "(défaut)"
        if r.crashed or r.timeout: S.failed(f"{lab} → crash/timeout"); continue
        bad = []
        if r.out and not r.out.endswith("\n"): bad.append("pas de \\n final")
        lines = r.out.split("\n")[:-1]
        if any(l == "" for l in lines): bad.append("ligne vide")
        wrong = [l for l in lines if l not in OPS]
        if wrong: bad.append(f"lignes invalides : {wrong[:3]!r}")
        if r.err: bad.append(f"stderr non vide : {r.err[:60]!r}")
        if bad: S.failed(f"{lab} : format", "\n".join(bad))
        else: S.passed(f"{lab} : uniquement des ops séparées par \\n", True)

    section("Déjà trié → 0 opération (toutes stratégies)")
    for n in (1, 2, 3, 5, 100, 500):
        nums = sorted(rand_list(n))
        for fl in ([], *[[s] for s in STRATS]):
            r = ps(*fl, *nums)
            lab = f"{' '.join(fl) or '(défaut)'} n={n} trié"
            if r.crashed: S.failed(f"{lab} → CRASH {sig_name(r.rc)}")
            elif r.out: S.failed(f"{lab} → {len(r.ops())} ops au lieu de 0")
            else: S.passed(lab)
    S.info("OK si aucune erreur ci-dessus")

def t_small(quick):
    section("Petites tailles — toutes les permutations")
    for n, limit in ((2, 1), (3, 3), (4, None), (5, 12)):
        perms = list(itertools.permutations(range(n)))
        if quick and n == 5: perms = random.sample(perms, 40)
        worst = {}
        for fl in ([], *[[s] for s in STRATS]):
            key = " ".join(fl) or "(défaut)"
            worst[key] = 0
            before = S.ko
            for p in perms:
                nums = [x * 7 - 10 for x in p]  # valeurs non contiguës + négatifs
                r = ps(*fl, *nums)
                if r.crashed or r.timeout:
                    S.failed(f"{key} {nums} → crash/timeout"); continue
                ok, why = simulate(nums, r.ops())
                if not ok: S.failed(f"{key} {nums} → KO : {why}"); continue
                worst[key] = max(worst[key], len(r.ops()))
            if S.ko == before: S.ok += 1
        lim = f" (barème éval : ≤ {limit})" if limit else ""
        S.info(f"n={n} ({len(perms)} perms) pire cas : " +
               ", ".join(f"{k}={v}" for k, v in worst.items()) + lim)
        if limit and worst["(défaut)"] > limit:
            S.warned(f"n={n} : le mode par défaut dépasse {limit} ops dans le pire cas ({worst['(défaut)']})")

def t_disorder():
    section("Adaptive — régimes de disorder (< 0.2 / 0.2–0.5 / ≥ 0.5)")
    targets = [0.0, 0.02, 0.1, 0.19, 0.21, 0.35, 0.49, 0.51, 0.7, 0.9, 1.0]
    for n in (100, 500):
        for t in targets:
            if t == 0.0: nums, d = sorted(rand_list(n)), 0.0
            elif t == 1.0: nums = sorted(rand_list(n), reverse=True); d = 1.0
            else: nums, d = with_disorder(n, t)
            regime = "low (O(n²))" if d < 0.2 else ("medium (O(n√n))" if d < 0.5 else "high (O(n log n))")
            cnt = check_sort(nums, ("--adaptive",), label=f"n={n} disorder={d:.3f}")
            if cnt is not None:
                S.info(f"n={n:<3} disorder={d:.3f} {c(DIM, regime):<28} → {cnt} ops")
    S.info("Vérifie avec --bench que la stratégie interne change bien selon le régime.")

def t_flags():
    section("Sélecteurs de stratégie")
    nums = rand_list(100)
    outs = {}
    for fl in ([], *[[s] for s in STRATS]):
        r = ps(*fl, *nums)
        lab = " ".join(fl) or "(défaut)"
        if r.crashed or r.timeout: S.failed(f"{lab} → crash/timeout"); continue
        ok, why = simulate(nums, r.ops())
        if ok: S.passed(f"{lab} trie 100 nombres ({len(r.ops())} ops)", True); outs[lab] = r.out
        else: S.failed(f"{lab} → KO : {why}")
    if "(défaut)" in outs and "--adaptive" in outs:
        if outs["(défaut)"] == outs["--adaptive"]: S.passed("défaut == --adaptive", True)
        else: S.warned("la sortie par défaut diffère de --adaptive (le défaut DOIT être adaptive)")
    distinct = len(set(v for k, v in outs.items() if k in ("--simple", "--medium", "--complex")))
    if distinct < 3: S.warned("--simple/--medium/--complex donnent des sorties identiques : vraiment 3 algos ?")

    section("Position / combinaison des flags")
    for args in (["--complex", "--bench"], ["--bench", "--complex"], ["--bench"]):
        r = ps(*args, *nums)
        lab = " ".join(args) + " <nums>"
        if r.crashed or r.timeout or r.err == ERR:
            S.failed(f"{lab} → " + ("Error" if r.err == ERR else "crash/timeout")); continue
        ok, why = simulate(nums, r.ops())
        (S.passed(lab, True) if ok else S.failed(f"{lab} → KO : {why}"))
    for args in (["--simple", "--complex", "3", "1", "2"], ["3", "1", "2", "--simple"],
                 ["--bench"], ["--simple"]):
        r = ps(*args)
        res = ("Error" if r.err == ERR else "CRASH" if r.crashed else
               "rien affiché" if not r.out and not r.err else "accepté")
        if r.crashed: S.failed(f"{' '.join(args)} → CRASH {sig_name(r.rc)}"); continue
        S.info(f"{' '.join(args)!s:<40} → {res} {c(DIM, '(comportement à justifier)')}")

    section("Toutes les stratégies sur tailles variées")
    for n in (6, 10, 25, 64, 100, 250, 500):
        for s in STRATS:
            check_sort(rand_list(n), (s,), label=f"{s} n={n}")
    S.info("OK si aucune erreur ci-dessus")

def t_bench():
    section("Mode --bench (stderr)")
    for s in STRATS + [None]:
        nums = rand_list(100)
        flags = ["--bench"] + ([s] if s else [])
        lab = " ".join(flags)
        r = ps(*flags, *nums)
        if r.crashed or r.timeout: S.failed(f"{lab} → crash/timeout"); continue
        ops = r.ops()
        ok, why = simulate(nums, ops)
        if not ok: S.failed(f"{lab} → stdout KO : {why}"); continue
        plain = ps(*([s] if s else []), *nums)
        if plain.out != r.out: S.warned(f"{lab} : stdout diffère de la version sans --bench")
        err = r.err
        problems = []
        if not err.strip(): problems.append("rien sur stderr")
        if any(l.strip() not in OPS for l in r.out.splitlines()): problems.append("stats mélangées dans stdout")
        d_exp = disorder(nums) * 100
        m = re.findall(r"(\d+(?:[.,]\d+)?)\s*%", err)
        if not m: problems.append("disorder en % introuvable")
        else:
            vals = [float(x.replace(",", ".")) for x in m]
            if not any(abs(v - d_exp) < 0.011 for v in vals):
                problems.append(f"disorder affiché {m} ≠ attendu {d_exp:.2f}%")
            if not re.search(r"\d+[.,]\d{2}\s*%", err): problems.append("disorder pas à 2 décimales")
        if not re.search(r"\b(simple|medium|complex|adaptive)\b", err, re.I):
            problems.append("nom de stratégie introuvable")
        if not re.search(r"O\(", err): problems.append("classe de complexité O(...) introuvable")
        if str(len(ops)) not in re.findall(r"\d+", err): problems.append(f"total {len(ops)} introuvable")
        for op in OPS:
            mm = re.search(rf"(?<![a-z]){op}(?![a-z])\D{{0,6}}?(\d+)", err)
            if not mm: problems.append(f"compteur '{op}' introuvable"); continue
            if int(mm.group(1)) != ops.count(op):
                problems.append(f"{op} = {mm.group(1)} affiché, réel = {ops.count(op)}")
        if problems: S.failed(lab, "\n".join(problems) + "\n--- stderr ---\n" + err)
        else: S.passed(f"{lab} : disorder, stratégie, total et 11 compteurs corrects", True)
    r = ps(*rand_list(20))
    if r.err: S.failed("sans --bench, stderr doit être vide", r.err)
    else: S.passed("sans --bench → stderr vide", True)
    print(c(DIM, "  Exemple de ta sortie --bench :"))
    for line in ps("--bench", *rand_list(100)).err.splitlines()[:16]:
        print("    " + c(DIM, line))

def t_perf(runs, checker_bin):
    section(f"Benchmark de performance ({runs} tirages par taille)")
    grades = {100: (700, 1500, 2000), 500: (5500, 8000, 12000)}
    for fl in ([], ["--complex"], ["--medium"]):
        lab = " ".join(fl) or "(défaut/adaptive)"
        for n, (exc, good, pas) in grades.items():
            counts, fails = [], 0
            for _ in range(runs):
                nums = rand_list(n, -2**31, 2**31 - 1)
                r = ps(*fl, *nums)
                if r.crashed or r.timeout or not simulate(nums, r.ops())[0]:
                    fails += 1
                    if fails == 1: S.failed(f"{lab} n={n} → KO/crash", fmt_args(nums, 500))
                    continue
                counts.append(len(r.ops()))
                if checker_bin and _ == 0:
                    cr = run([checker_bin, *map(str, nums)], stdin=r.out)
                    if cr.out.strip() != "OK": S.failed(f"{checker_bin} dit {cr.out.strip()!r} pour n={n}")
            if not counts: continue
            mx, avg, mn = max(counts), sum(counts) / len(counts), min(counts)
            g = (c(GREEN, "EXCELLENT") if mx < exc else c(GREEN, "BON") if mx < good
                 else c(YEL, "PASSE") if mx < pas else c(RED, "ÉCHEC"))
            print(f"  {lab:<18} n={n:<3}  min {mn:<6} moy {avg:<8.0f} max {mx:<6} → {g}")
            if fl == [] and mx >= pas: S.failed(f"n={n} : max {mx} ≥ {pas} (minimum requis)")
            elif fl == []: S.ok += 1

def t_growth():
    section("Croissance du nb d'ops (estimation empirique de la complexité)")
    sizes = [50, 100, 200, 400, 800]
    expect = {"--simple": (2.0, "O(n²)"), "--medium": (1.5, "O(n√n)"), "--complex": ("1.1–1.2", "O(n log n)")}
    for s, (exp, name) in expect.items():
        pts = []
        for n in sizes:
            tot = 0
            for _ in range(3):
                r = ps(s, *rand_list(n))
                if r.crashed or r.timeout: break
                tot += len(r.ops())
            else:
                pts.append((n, tot / 3)); continue
            S.failed(f"{s} n={n} → crash/timeout"); break
        if len(pts) < 3: continue
        xs = [math.log(n) for n, _ in pts]; ys = [math.log(max(v, 1)) for _, v in pts]
        mx, my = sum(xs) / len(xs), sum(ys) / len(ys)
        slope = sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / sum((x - mx) ** 2 for x in xs)
        nlogn = [v / (n * math.log2(n)) for n, v in pts]
        detail = "  ".join(f"n={n}:{int(v)}" for n, v in pts)
        print(f"  {s:<10} pente log-log ≈ {slope:.2f} (attendu ≈ {exp} pour {name})   {c(DIM, detail)}")
        if s == "--complex":
            print(f"  {'':<10} {c(DIM, 'ops/(n·log2 n) = ' + ', '.join(f'{x:.2f}' for x in nlogn) + ' (doit rester ~constant)')}")
        limit = {"--simple": 2.25, "--medium": 1.75, "--complex": 1.35}[s]
        if slope > limit: S.warned(f"{s} : pente {slope:.2f} > {limit} → la classe annoncée {name} semble fausse")
        else: S.ok += 1
    S.info("La pente est une borne empirique : O(n²) est une borne SUP, un --simple plus rapide reste valide.")

def t_valgrind():
    section("Fuites mémoire (valgrind)")
    vg = shutil.which("valgrind")
    if not vg:
        S.info("valgrind non installé → section ignorée (sur macOS : `leaks -atExit -- ./push_swap ...`)")
        return
    cases = [[], ["1"], ["2", "1"], ["3", "2", "1"], ["1", "one"], ["1", "1"], ["2147483648"], [""],
             ["--unknown", "1"], *[[s, *map(str, rand_list(100))] for s in STRATS],
             ["--bench", *map(str, rand_list(50))], list(map(str, rand_list(500)))]
    for args in cases:
        r = run([vg, "--leak-check=full", "--show-leak-kinds=all", "--errors-for-leak-kinds=all",
                 "--error-exitcode=42", "--track-fds=no", PUSH_SWAP, *args], timeout=120)
        lab = "./push_swap " + (fmt_args(args, 4) if args else "(rien)")
        if r.timeout: S.warned(f"{lab} → timeout valgrind"); continue
        leak = re.search(r"in use at exit: ([\d,]+) bytes", r.err)
        errs = re.search(r"ERROR SUMMARY: (\d+)", r.err)
        if r.rc == 42 or (leak and leak.group(1) != "0") or (errs and errs.group(1) != "0"):
            S.failed(lab, "\n".join(l for l in r.err.splitlines()
                                    if "lost" in l or "in use" in l or "Invalid" in l or "ERROR" in l))
        else: S.passed(lab)
    S.info("OK si aucune erreur ci-dessus")

def t_checker(chk):
    section(f"Bonus — ton checker ({chk})")
    def ck(args, stdin, expect_out, expect_err="", lab=None):
        r = run([chk, *map(str, args)], stdin=stdin)
        lab = lab or f"checker {fmt_args(args, 6)} <<< {stdin[:30]!r}"
        if r.crashed or r.timeout: S.failed(f"{lab} → crash/timeout"); return
        if r.out != expect_out or r.err != expect_err:
            S.failed(lab, f"stdout={r.out!r} (attendu {expect_out!r})  stderr={r.err!r} (attendu {expect_err!r})")
        else: S.passed(lab)
    ck([], "", "", "", "checker sans argument → rien")
    ck([3, 2, 1, 0], "rra\npb\nsa\nrra\npa\n", "OK\n")
    ck([3, 2, 1, 0], "sa\nrra\npb\n", "KO\n")
    ck([3, 2, "one", 0], "", "", "Error\n")
    ck(["", 1], "", "", "Error\n")
    ck([1, 1], "", "", "Error\n")
    ck(["2147483648"], "", "", "Error\n")
    ck([1, 2, 3], "", "OK\n", lab="trié + aucune instruction → OK")
    ck([2, 1, 3], "", "KO\n", lab="non trié + aucune instruction → KO")
    ck([1, 2, 3], "pb\n", "KO\n", lab="a trié mais b non vide → KO")
    ck([1, 2, 3], "pb\npa\n", "OK\n")
    ck([2, 1], "sa\nfoo\n", "", "Error\n", "instruction inexistante → Error")
    ck([2, 1], " sa\n", "", "Error\n", "espace avant → Error")
    ck([2, 1], "sa \n", "", "Error\n", "espace après → Error")
    ck([2, 1], "SA\n", "", "Error\n", "majuscules → Error")
    ck([2, 1], "sasa\n", "", "Error\n", "deux ops collées → Error")
    ck([1], "sa\nsb\nss\nra\nrb\nrr\nrra\nrrb\nrrr\npa\n", "OK\n", lab="ops sur stacks vides/1 elt → pas de crash")
    for n in (5, 100, 500):
        nums = rand_list(n)
        out = ps(*nums).out
        ck(nums, out, "OK\n", lab=f"sortie de push_swap n={n} → OK")
        ops = out.split("\n")[:-1]
        if ops:
            ops.pop(random.randrange(len(ops)))
            ck(nums, "\n".join(ops) + "\n", "KO\n" if not simulate(nums, ops)[0] else "OK\n",
               lab=f"push_swap n={n} avec une op retirée")
    S.info("OK si aucune erreur ci-dessus")

# ───────────────────────────── main ─────────────────────────────
def main():
    global PUSH_SWAP
    ap = argparse.ArgumentParser(description="Tester push_swap (sujet v1.2)")
    ap.add_argument("-p", "--push-swap", default="./push_swap")
    ap.add_argument("-b", "--bonus-checker", help="chemin de TON checker (bonus)")
    ap.add_argument("-c", "--checker", help="checker_linux officiel (optionnel)")
    ap.add_argument("--runs", type=int, default=None)
    ap.add_argument("--quick", action="store_true")
    ap.add_argument("--seed", type=int, default=None)
    ap.add_argument("--only", default="")
    a = ap.parse_args()

    PUSH_SWAP = os.path.abspath(a.push_swap)
    if not os.access(PUSH_SWAP, os.X_OK):
        sys.exit(f"Binaire introuvable ou non exécutable : {PUSH_SWAP} (lance `make` d'abord)")
    seed = a.seed if a.seed is not None else random.randrange(10**6)
    random.seed(seed)
    runs = a.runs or (10 if a.quick else 100)
    chk = a.checker or (os.path.abspath("checker_linux") if os.access("checker_linux", os.X_OK) else None)
    only = set(x.strip() for x in a.only.split(",") if x.strip())
    want = lambda s: not only or s in only

    print(c(BOLD, f"push_swap tester — {PUSH_SWAP}") + c(DIM, f"   (seed {seed} → rejouer avec --seed {seed})"))
    if want("errors"): t_errors()
    if want("format"): t_format()
    if want("small"): t_small(a.quick)
    if want("disorder"): t_disorder()
    if want("flags"): t_flags()
    if want("bench"): t_bench()
    if want("perf"): t_perf(runs, chk)
    if want("growth"): t_growth()
    if want("valgrind"): t_valgrind()
    if a.bonus_checker and want("checker"): t_checker(os.path.abspath(a.bonus_checker))

    print(f"\n{c(BOLD, 'Résumé')} : {c(GREEN, str(S.ok) + ' OK')}  {c(RED, str(S.ko) + ' KO')}  "
          f"{c(YEL, str(S.warn) + ' avertissements')}")
    sys.exit(1 if S.ko else 0)

if __name__ == "__main__":
    main()
