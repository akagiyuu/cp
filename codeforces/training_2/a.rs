use std::collections::HashMap;
use std::fmt::Write;
use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn main() {
    let mut lines = io::stdin().lines();
    let n = readline!(lines).parse::<usize>().unwrap();
    let people_in_timezones = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse::<u32>().unwrap())
        .collect::<Vec<_>>();
    let line = &readline!(lines);
    let (min_time, max_time) = line.split_once(' ').unwrap();
    let min_time = min_time.parse::<usize>().unwrap();
    let max_time = max_time.parse::<usize>().unwrap();
    let mut people_free_in_times = vec![0; n + 1];
    for (offset, people_in_timezone) in people_in_timezones.iter().enumerate() {
        for i in min_time..max_time {
            people_free_in_times[(i + n + offset - 1) % n + 1] += people_in_timezone;
        }
    }
    let result = people_free_in_times
        .iter()
        .enumerate()
        .max_by(|a, b| {
            if a.1 == b.1 {
                b.0.cmp(&a.0)
            } else {
                a.1.cmp(b.1)
            }
        })
        .unwrap()
        .0;
    println!("{}", result);
}
