use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn gcd(a: u64, b: u64) -> u64 {
    let (mut a, mut b) = (a.max(b), a.min(b));
    while b != 0 {
        (a, b) = (b, a % b);
    }
    a
}

fn solve(a: Vec<i128>, k: i128) -> i128 {
    let mut diff = a[0].abs_diff(k) as u64;
    for &x in a.iter().skip(1) {
        if (x - k) * (a[0] - k) < 0 {
            return -1;
        }
        diff = gcd(diff, x.abs_diff(k) as u64);
    }

    let diff = if a[0] >= k {
        diff as i128
    } else {
        -(diff as i128)
    };

    let mut count = 0;
    for &x in a.iter() {
        if diff == 0 {
            if x == k {
                continue;
            } else {
                return -1;
            }
        }
        let n = (x - k) / diff;
        if n < 1 {
            return -1;
        }
        count += n - 1;
    }
    count
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (_, k) = line.split_once(' ').unwrap();
        let k = k.parse().unwrap();
        let a = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        println!("{}", solve(a, k));
    }
}
