use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(n: usize, k: usize) {
    if n < k {
        println!("NO");
        return;
    }

    if (n - k) % 2 == 0 {
        println!("YES");
        for _ in 0..k - 1 {
            print!("{} ", 1);
        }
        println!("{}", n - (k - 1));
        return;
    }
    if n % 2 == 0 && n > 2 * (k - 1) {
        println!("YES");
        for _ in 0..k - 1 {
            print!("{} ", 2);
        }
        println!("{}", n - 2 * (k - 1));
        return;
    }
    println!("NO");
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<u32>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (n, k) = line.split_once(' ').unwrap();
        let n = n.parse().unwrap();
        let k = k.parse().unwrap();
        solve(n, k);
    }
}
