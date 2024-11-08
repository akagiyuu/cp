use std::{
    collections::{HashSet, VecDeque},
    io,
};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn gcd(a: u64, b: u64) -> u64 {
    if a < b {
        return gcd(b, a);
    }

    if b == 0 {
        return a;
    }

    gcd(b, a % b)
}

fn solve(heights: Vec<Vec<i64>>, types: Vec<Vec<u64>>, k: usize) -> bool {
    let row_count = heights.len();
    let column_count = heights[0].len();

    let mut sum = [0; 2];

    for i in 0..row_count {
        for j in 0..column_count {
            sum[types[i][j] as usize] += heights[i][j];
        }
    }
    if sum[0] == sum[1] {
        return true;
    }

    let mut prefix = vec![vec![0; column_count]; row_count];
    prefix[0][0] = types[0][0];

    for i in 1..row_count {
        prefix[i][0] = prefix[i - 1][0] + types[i][0];
    }

    for j in 1..column_count {
        prefix[0][j] = prefix[0][j - 1] + types[0][j];
    }

    for i in 1..row_count {
        for j in 1..column_count {
            prefix[i][j] = types[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

    let mut divisors = HashSet::new();

    for i in 0..row_count - k + 1 {
        for j in 0..column_count - k + 1 {
            let i2 = i + k - 1;
            let j2 = j + k - 1;

            let type_one_count = match (i, j) {
                (0, 0) => prefix[i2][j2],
                (0, _) => prefix[i2][j2] - prefix[i2][j - 1],
                (_, 0) => prefix[i2][j2] - prefix[i - 1][j2],
                _ => prefix[i2][j2] - prefix[i - 1][j2] - prefix[i2][j - 1] + prefix[i - 1][j - 1],
            };
            let divisor = (2 * type_one_count).abs_diff((k * k) as u64);
            if divisor > 0 {
                divisors.insert(divisor);
            }
        }
    }
    let divisors = divisors.into_iter().collect::<Vec<_>>();
    if divisors.is_empty() {
        return false;
    }
    let mut divisors_gcd = divisors[0];
    for &x in divisors.iter().skip(1) {
        divisors_gcd = gcd(divisors_gcd, x);
    }

    let diff = sum[0].abs_diff(sum[1]);

    diff % divisors_gcd == 0
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let line: Vec<_> = readline!(lines)
            .split_whitespace()
            .map(|x| x.parse::<usize>().unwrap())
            .collect();

        let n = line[0];
        let k = line[2];

        let heights: Vec<_> = (0..n)
            .map(|_| {
                readline!(lines)
                    .split_whitespace()
                    .map(|x| x.parse::<i64>().unwrap())
                    .collect::<Vec<_>>()
            })
            .collect();

        let types: Vec<_> = (0..n)
            .map(|_| {
                readline!(lines)
                    .bytes()
                    .map(|x| (x - b'0') as u64)
                    .collect::<Vec<_>>()
            })
            .collect();
        println!(
            "{}",
            if solve(heights, types, k) {
                "YES"
            } else {
                "NO"
            }
        );
    }
}
