use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

const N: usize = 200;

fn solve(a: Vec<usize>) -> usize {
    let mut prefix = vec![[0; N]; a.len()];
    prefix[0][a[0]] = 1;

    for i in 1..a.len() {
        prefix[i] = prefix[i - 1];
        prefix[i][a[i]] += 1;
    }

    let mut max_length = 0;
    for i in 0..a.len() {
        for j in i..a.len() {
            let y = prefix[j]
                .iter()
                .zip(if i == 0 { [0; N] } else { prefix[i - 1] })
                .map(|(x, y)| x - y)
                .max()
                .unwrap();

            let mut max_x = 0;
            for k in 0..N {
                let left = if i == 0 { 0 } else { prefix[i - 1][k] };
                let right = if j == a.len() - 1 {
                    0
                } else {
                    prefix[a.len() - 1][k] - prefix[j][k]
                };
                let x = left.min(right);
                max_x = max_x.max(x);
            }
            let length = y + max_x * 2;
            max_length = max_length.max(length);
        }
    }

    max_length
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        lines.next();
        let a = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<usize>().unwrap() - 1)
            .collect();
        println!("{}", solve(a));
    }
}
