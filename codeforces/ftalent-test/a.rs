use std::{
    collections::HashMap,
    io::{self, BufRead},
};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(s: &str) {
    let mut stack = vec![];
    for c in s.chars() {
        match c {
            ' ' | ',' | '.' | '?' | '!' | ';' => {
                while let Some(cur_c) = stack.pop() {
                    print!("{}", cur_c);
                }
                print!("{}", c);
            }
            c => stack.push(c),
        }
    }
    while let Some(cur_c) = stack.pop() {
        print!("{}", cur_c);
    }
    println!()
}

fn main() {
    let mut lines = io::stdin().lock().lines();
    for line in lines {
        let line = line.unwrap();
        solve(&line);
    }
}
