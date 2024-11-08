use std::io;

const MOD: u128 = 1_000_000_007;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn pow(a: u128, b: u128) -> u128 {
    let mut result = 1;
    let mut b = b;
    let mut a = a;
    while b > 0 {
        if b % 2 == 1 {
            result *= a;
            result %= MOD;
        }
        a *= a;
        a %= MOD;
        b /= 2;
    }
    result
}

fn build(n: usize) -> (Vec<u128>, Vec<u128>) {
    let mut fact = Vec::with_capacity(n + 1);
    fact.push(1);
    for i in 1..=n {
        fact.push((fact[i - 1] * i as u128) % MOD);
    }

    let mut ifact = vec![0; n + 1];
    ifact[n] = pow(fact[n], MOD - 2);
    for i in (0..=n - 1).rev() {
        ifact[i] = ifact[i + 1] * (i + 1) as u128;
        ifact[i] %= MOD;
    }

    (fact, ifact)
}

fn _n_choose_k(n: u128, k: u128, fact: &[u128], ifact: &[u128]) -> u128 {
    if k > n {
        return 0;
    }

    (fact[n as usize] * ifact[k as usize]) % MOD * ifact[(n - k) as usize] % MOD
}

fn n_choose_k(n: u128, k: u128, fact: &[u128], ifact: &[u128]) -> u128 {
    if k > n {
        return 0;
    }
    let mut n = n;
    let mut k = k;
    let mut result = 1;
    while n > 0 {
        result = result * _n_choose_k(n % MOD, k % MOD, fact, ifact) % MOD;
        n /= MOD;
        k /= MOD;
    }
    result
}

fn solve(a: Vec<u128>, k: usize, fact: &[u128], ifact: &[u128]) -> u128 {
    let mut a = a;
    a.sort_by(|a, b| b.cmp(a));

    let mut count_pre = 0u128;
    let mut pre = 0;
    for &x in a.iter().take(k) {
        if x == pre {
            count_pre += 1;
        } else {
            pre = x;
            count_pre = 1;
        }
    }

    let count_tail = a.iter().skip(k).filter(|&&x| x == pre).count() as u128;
    n_choose_k(count_pre + count_tail, count_pre, fact, ifact) % MOD
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    let (fact, ifact) = build(1_000_000);
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (_, k) = line.split_once(' ').unwrap();
        let k: usize = k.parse().unwrap();
        let a = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        println!("{}", solve(a, k, &fact, &ifact));
    }
}
