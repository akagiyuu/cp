use std::cmp;
use std::io;

macro_rules! readline_vec {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();

        line.split_ascii_whitespace()
            .map(|c| c.parse().unwrap())
            .collect()
    }};
}

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line.parse().unwrap()
    }};
}

fn main() {
    let mut lines = io::stdin().lines();
    lines.next();
    let a: Vec<usize> = readline_vec!(lines);
}
