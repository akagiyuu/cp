use std::{collections::VecDeque, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn eratosthenes_sieve(n: usize) -> Vec<bool> {
    let mut sieve = vec![true; n + 1];
    sieve[0] = false;
    sieve[1] = false;

    for i in 2..=n {
        if !sieve[i] {
            continue;
        }
        for j in (2 * i..=n).step_by(i) {
            sieve[j] = false;
        }
    }

    sieve
}

fn get_primes(sieve: &[bool]) -> Vec<u128> {
    sieve
        .iter()
        .enumerate()
        .filter_map(|(x, &is_prime)| if is_prime { Some(x as u128) } else { None })
        .collect()
}

fn solve(n: u128, prime_i: usize, primes: &[u128]) -> u128 {
    if n == 1 {
        return 1;
    }

    let mut min_num = u128::MAX;
    for i in 2..=n {
        if n % i != 0 {
            continue;
        }

        let Some(pow) = primes[prime_i].checked_pow(i as u32 - 1) else {
            continue;
        };
        let Some(num) = pow.checked_mul(solve(n / i, prime_i + 1, primes)) else {
            continue;
        };
        min_num = min_num.min(num);
    }

    min_num
}

fn main() {
    let mut lines = io::stdin().lines();
    let n: u128 = readline!(lines).parse().unwrap();
    let primes = get_primes(&eratosthenes_sieve(100_000));
    println!("{}", solve(n, 0, &primes));
}
