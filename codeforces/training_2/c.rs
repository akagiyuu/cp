use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: u64, b: u64) -> bool {
    let product = a * b;
    let mut approximate_cube_root = (product as f64).powf(1. / 3.).floor() as u64;
    while approximate_cube_root.pow(3) < product {
        approximate_cube_root += 1;
    }
    if approximate_cube_root.pow(3) != product {
        return false;
    }

    a % approximate_cube_root == 0 && b % approximate_cube_root == 0
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (a, b) = line.split_once(' ').unwrap();
        let a = a.parse().unwrap();
        let b = b.parse().unwrap();
        println!("{}", if solve(a, b) { "YES" } else { "NO" });
    }
}
