use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn max_sum_from_start(a: &[i64]) -> i64 {
    let mut partial_sum = a[0];
    let mut max_sum = a[0];
    for x in a.iter().skip(1) {
        partial_sum += x;
        if partial_sum > max_sum {
            max_sum = partial_sum;
        }
    }
    max_sum
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count: usize = readline!(lines).parse().unwrap();

    for _ in 0..test_case_count {
        lines.next();
        let r: Vec<_> = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<i64>().unwrap())
            .collect();
        let max_start_r = max_sum_from_start(&r).max(0);

        lines.next();
        let b: Vec<_> = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<i64>().unwrap())
            .collect();
        let max_start_b = max_sum_from_start(&b).max(0);

        println!(
            "{}",
            max_start_r + max_start_b
        );
    }
}
