use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<i64>) -> usize {
    let mut a = a;
    a.insert(0, -1);
    let mut max_length = 1;
    let mut left = 1;
    let mut change_count = 0;
    let mut change_index = 0;
    let mut temp = 0;
    for right in 2..a.len() {
        if a[right] > a[right - 1] {
            max_length = max_length.max(right - left + 1);
            continue;
        }

        if change_count == 1 {
            left = change_index + 1;
            a[change_index] = temp;
        }

        if a[right - 1] + 2 <= a[right + 1] {
            change_index = right;
            temp = a[right];
            a[right] = a[right - 1] + 1;
        } else {
            change_index = right - 1;
            temp = a[right - 1];
            a[right - 1] = a[right - 2] + 1;
        }
        change_count = 1;
        max_length = max_length.max(right - left + 1);
    }

    max_length
}

fn main() {
    let mut lines = io::stdin().lines();
    lines.next();
    let a = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse::<i64>().unwrap())
        .collect();
    println!("{}", solve(a));
}
