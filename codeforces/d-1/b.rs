use std::{cmp::Ordering, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn cal_gcd(a: u64, b: u64) -> u64 {
    let (mut a, mut b) = (a.min(b), a.max(b));
    while b != 0 {
        (a, b) = (b, a % b);
    }
    a
}

fn solve(a: u64, b: u64, c: u64, d: u64) -> (u64, u64) {
    match (b * c).cmp(&(d * a)) {
        Ordering::Greater => {
            let num = b * c - d * a;
            let denom = b * c;
            let gcd = cal_gcd(num, denom);
            (num / gcd, denom / gcd)
        }
        Ordering::Less => {
            let num = d * a - b * c;
            let denom = d * a;
            let gcd = cal_gcd(num, denom);
            (num / gcd, denom / gcd)
        }
        Ordering::Equal => {
            let num = d * a - b * c;
            let denom = (d * a).max(b * c);
            let gcd = cal_gcd(num, denom);
            (num / gcd, denom / gcd)
        }
    }
}

fn main() {
    let mut lines = io::stdin().lines();
    let line = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse::<u64>().unwrap())
        .collect::<Vec<_>>();
    let (a, b) = solve(line[0], line[1], line[2], line[3]);
    println!("{}/{}", a, b);
}
