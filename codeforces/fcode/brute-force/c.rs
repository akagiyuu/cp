use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<u32>) -> bool {
    let even_parity = a[0] % 2;
    let odd_parity = a[1] % 2;

    for i in 2..a.len() {
        let expected_parity = if i % 2 == 0 { even_parity } else { odd_parity };
        if a[i] % 2 != expected_parity {
            return false;
        }
    }

    true
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<u32>().unwrap();
    for _ in 0..test_case_count {
        lines.next();
        let a = readline!(lines).split_whitespace().map(|x| x.parse::<u32>().unwrap()).collect::<Vec<_>>();
        println!("{}", if solve(a) { "YES" } else { "NO" });
    }
}
