use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count: usize = readline!(lines).parse().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (_, q) = line.split_once(' ').unwrap();
        let q: usize = q.parse().unwrap();

        let mut seq: Vec<_> = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<u32>().unwrap())
            .collect();
        seq.sort_by(|a, b| b.cmp(a));

        let mut sums = vec![0; seq.len()];
        sums[0] = seq[0];

        for i in 1..seq.len() {
            sums[i] = sums[i - 1] + seq[i];
        }

        for _ in 0..q {
            let value: u32 = readline!(lines).parse().unwrap();
            let pos = match sums.binary_search(&value) {
                Ok(v) => v,
                Err(v) => v,
            } + 1;
            println!(
                "{}",
                if pos == seq.len() + 1 { -1 } else { pos as i32 }
            );
        }
    }
}
