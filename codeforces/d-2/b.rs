use std::{collections::HashMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn get_min_max_digit(n: &str, dp: &mut HashMap<String, (u8, u8)>) -> (u8, u8) {
    match dp.get(n) {
        Some(&v) => v,
        None => {
            let (pre_min, pre_max) = get_min_max_digit(&n[1..], dp);
            let cur_ditgit = n.chars().next().unwrap().to_digit(10).unwrap() as u8;
            let min = pre_min.min(cur_ditgit);
            let max = pre_max.max(cur_ditgit);
            let v = (min, max);
            dp.insert(n.to_string(), v);
            v
        }
    }
}

fn main() {
    let mut dp = HashMap::new();
    for i in 0..=9 {
        dp.insert(i.to_string(), (i, i));
    }
    let mut lines = io::stdin().lines();
    let test_case_count: usize = readline!(lines).parse().unwrap();

    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (l, r) = line.split_once(' ').unwrap();
        let l: u64 = l.parse().unwrap();
        let r: u64 = r.parse().unwrap();

        let mut min_num = 0;
        let mut min_luckiness = 10;
        for i in l..=r {
            let (min , max) = get_min_max_digit(&i.to_string(), &mut dp);
            let luckiness = max - min;
            if luckiness < min_luckiness {
                min_num = i;
                min_luckiness = luckiness
            }
            if min_luckiness == 0 {
                break;
            }
        }
        println!("{}", min_num);
    }
}
