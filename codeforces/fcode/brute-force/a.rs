use std::fmt::Write;
use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(s: String) {
    let mut result = String::new();
    let mut count = 0;
    for (i, c) in s.chars().enumerate() {
        if c == '0' {
            continue;
        }
        count += 1;
        write!(result, "{:0<width$} ", c, width = s.len() - i).unwrap();
    }
    println!("{}", count);
    println!("{}", result);
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<u32>().unwrap();
    for _ in 0..test_case_count {
        let s = readline!(lines);
        solve(s);
    }
}
