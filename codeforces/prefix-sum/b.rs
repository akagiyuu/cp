use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn main() {
    let mut lines = io::stdin().lines();
    let line: Vec<_> = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse::<usize>().unwrap())
        .collect();
    let n = line[0];
    let m = line[1];
    let k = line[2];

    let mut a: Vec<_> = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse::<i64>().unwrap())
        .collect();

    let mut operations: Vec<_> = (0..m)
        .map(|_| {
            let line: Vec<_> = readline!(lines)
                .split_ascii_whitespace()
                .map(|x| x.parse::<usize>().unwrap())
                .collect();
            (line[0] - 1, line[1] - 1, line[2] as i64)
        })
        .collect();

    let mut query_merged = vec![0i64; m];
    for _ in 0..k {
        let line = readline!(lines);
        let (x, y) = line.split_once(' ').unwrap();
        let x = x.parse::<usize>().unwrap() - 1;
        let y = y.parse::<usize>().unwrap() - 1;

        query_merged[x] += 1;
        if y + 1 < m {
            query_merged[y + 1] -= 1;
        }
    }

    let mut repeat_time = 0;
    for i in 0..m {
        repeat_time += query_merged[i];
        operations[i].2 *= repeat_time;
    }

    let mut operation_merged = vec![0; n];
    for i in 0..m {
        let (l, r, d) = operations[i];
        operation_merged[l] += d;
        if r + 1 < n {
            operation_merged[r + 1] -= d;
        }
    }

    let mut partial_sum = 0;
    for i in 0..n {
        partial_sum += operation_merged[i];
        a[i] += partial_sum;
    }
    for i in 0..n {
        print!("{} ", a[i]);
    }
}
