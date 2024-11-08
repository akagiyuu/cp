use std::{collections::HashMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<u64>, k: usize) -> Option<Vec<u64>> {
    if k == a.len() {
        return Some(a);
    }

    let mut nums = HashMap::new();
    for (i, &x) in a.iter().enumerate() {
        if nums.contains_key(&x) {
            continue;
        }

        nums.insert(x, i);
    }
    if nums.len() > k {
        return None;
    }
    for i in 1..=a.len() as u64 {
        if nums.len() == k {
            break;
        }
        if nums.contains_key(&i) {
            continue;
        }
        nums.insert(i, a.len() + nums.len());
    }
    let mut nums = nums.into_iter().collect::<Vec<_>>();
    nums.sort_by_key(|&(_, i)| i);
    let nums = nums.into_iter().map(|(x, _)| x).collect::<Vec<_>>();

    let mut result = vec![];

    let mut i = 0;
    while i < a.len() {
        for j in 0..k {
            result.push(nums[j]);
            if i < a.len() && a[i] == nums[j] {
                i += 1;
            }
        }
    }

    let length = result.len();
    while result.len() < 4 {
        for i in 0..length {
            result.push(result[i]);
        }
    }

    Some(result)
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (_, k) = line.split_once(' ').unwrap();
        let k: usize = k.parse().unwrap();
        let a = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        match solve(a, k) {
            Some(v) => {
                println!("{}", v.len());
                for x in v {
                    print!("{} ", x);
                }
            }
            None => print!("-1"),
        };
        println!();
    }
}
