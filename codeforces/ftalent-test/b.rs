use std::{cmp::Ordering, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn main() {
    let mut lines = io::stdin().lines();
    let n: usize = readline!(lines).parse().unwrap();
    let x: i64 = readline!(lines).parse().unwrap();
    let mut max_partial_sum = x;
    let mut max_partial_sum_indexs = vec![0];
    let mut max_sum = x;
    let mut max_sum_indexs = vec![0];
    for i in 1..n {
        let x: i64 = readline!(lines).parse().unwrap();
        if max_partial_sum > 0 {
            max_partial_sum += x;
            max_partial_sum_indexs.push(i);
        } else {
            max_partial_sum = x;
            max_partial_sum_indexs.clear();
            max_partial_sum_indexs.push(i);
        }

        if max_partial_sum > max_sum {
            max_sum = max_partial_sum;
            max_sum_indexs = max_partial_sum_indexs.clone();
        }
    }
    for x in max_sum_indexs {
        print!("{} ", x);
    }
    println!();
    println!("{}", max_sum);
}
