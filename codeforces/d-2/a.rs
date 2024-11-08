use std::{collections::HashMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn find_with_weight(weights: &[u64], k: u64) -> u64 {
    let mut choosen = vec![false; weights.len()];
    let mut team_count = 0;
    for i in 0..weights.len() {
        if choosen[i] {
            continue;
        }
        for j in i + 1..weights.len() {
            if choosen[j] {
                continue;
            }
            if weights[i] + weights[j] != k {
                continue;
            }
            choosen[i] = true;
            choosen[j] = true;
            team_count += 1;
            break;
        }
    }

    team_count
}

fn solve(weights: Vec<u64>) -> u64 {
    if weights.len() == 1 {
        return 0;
    }
    let mut weights_sum = HashMap::new();

    for i in 0..weights.len() {
        for j in i + 1..weights.len() {
            *weights_sum.entry(weights[i] + weights[j]).or_insert(0) += 1;
        }
    }

    let mut max_team_count = 0;
    for (s, _) in weights_sum {
        max_team_count = max_team_count.max(find_with_weight(&weights, s));
    }
    max_team_count
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        lines.next();
        let weights = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        println!("{}", solve(weights));
    }
}
