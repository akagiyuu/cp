use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<u128>) -> u128 {
    let n = a.len();
    if n == 1 {
        return a[0];
    }

    let mut even_sum = vec![0; n];
    even_sum[0] = a[0];
    let mut odd_sum = vec![0; n];
    odd_sum[0] = 0;
    for (i, x) in a.iter().enumerate().skip(1) {
        if i % 2 == 0 {
            even_sum[i] = even_sum[i - 1] + x;
            odd_sum[i] = odd_sum[i - 1];
        } else {
            even_sum[i] = even_sum[i - 1];
            odd_sum[i] = odd_sum[i - 1] + x;
        }
    }

    let mut max_diff = 0;

    for i in 0..n - 1 {
        for j in (i + 1..n).step_by(2) {
            let even = even_sum[j] - if i == 0 { 0 } else { even_sum[i - 1] };
            let odd = odd_sum[j] - if i == 0 { 0 } else { odd_sum[i - 1] };
            if odd > even {
                let value = odd - even;
                max_diff = max_diff.max(value);
            }
        }
    }

    even_sum[n - 1] + max_diff
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        lines.next();
        let a = readline!(lines)
            .split(' ')
            .map(|x| x.parse::<u128>().unwrap())
            .collect();
        println!("{}", solve(a));
    }
}
