use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<u64>, m: usize, k: usize) -> u64 {
    let mut dp = vec![vec![0; a.len()]; k + 1];
    let mut prefix = vec![a[0]; a.len()];
    for i in 1..a.len() {
        prefix[i] = prefix[i - 1] + a[i];
    }

    for i in 1..=k {
        dp[i][a.len() - m] = prefix[a.len() - 1]
            - if a.len() == m {
                0
            } else {
                prefix[a.len() - m - 1]
            };
        for j in (0..a.len() - m).rev() {
            dp[i][j] = dp[i][j + 1]
                .max(prefix[j + m - 1] - if j == 0 { 0 } else { prefix[j - 1] } + dp[i - 1][j + m]);
        }
    }
    dp[k][0]
}

fn main() {
    let mut lines = io::stdin().lines();
    let line: Vec<_> = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.to_string())
        .collect();

    let a = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    println!(
        "{}",
        solve(a, line[1].parse().unwrap(), line[2].parse().unwrap())
    );
}
