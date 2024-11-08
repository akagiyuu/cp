use std::io;

const MOD: u128 = 1_000_000_007;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn pow_2(n: u128) -> u128 {
    let mut n = n;
    let mut base = 2;
    let mut result = 1;

    while n > 0 {
        if n % 2 == 1 {
            result *= base;
            result %= MOD;
        }

        base *= base;
        base %= MOD;
        n /= 2;
    }

    result
}

fn solve(n: u128, m: u128, k: i64) -> u128 {
    // if i == n {
    //     for i in 0..n {
    //         for j in 0..m {
    //             let mut product = 1;
    //             for k in 0..n {
    //                 product *= test[k][j];
    //             }
    //             if product != k_val {
    //                 return 0;
    //             }
    //
    //             let mut product = 1;
    //             for k in 0..m {
    //                 product *= test[i][k];
    //             }
    //             if product != k_val {
    //                 return 0;
    //             }
    //         }
    //     }
    //     // print_grid(test);
    //     // println!();
    //     return 1;
    // }
    //
    // let mut count = 0;
    // for x in [-1, 1] {
    //     test[i][j] = x;
    //     let mut next_i = i;
    //     let mut next_j = j + 1;
    //     if next_j == m {
    //         next_j = 0;
    //         next_i += 1;
    //     }
    //     count += solve(n, m, k_val, test, next_i, next_j);
    // }

    let pow = (n - 1) * (m - 1);
    if k == -1 && n % 2 != m % 2 {
        0
    } else {
        pow_2(pow)
    }
}

fn main() {
    let mut lines = io::stdin().lines();
    // for n in 1..10 {
    //     for m in 1..5 {
    //         print!("{} {} -> ", n, m);
    //         println!(
    //             "{} ? {}",
    //             solve(n, m, -1, &mut vec![vec![0; m]; n], 0, 0),
    //             1 << ((n - 1) * (m - 1))
    //         );
    //     }
    //     println!()
    // }
    let line = readline!(lines);
    let line: Vec<_> = line.split_ascii_whitespace().collect();
    let n = line[0].parse().unwrap();
    let m = line[1].parse().unwrap();
    println!("{}", solve(n, m, line[2].parse().unwrap()));
}
