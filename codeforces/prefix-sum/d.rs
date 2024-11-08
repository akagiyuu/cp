use std::{collections::BTreeMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap(  );
        line
    }};
}

fn get_max_cover(n: usize, k: usize) -> (usize, u64) {
    if n < k {
        return (0, n as u64);
    }
    let mid_row_i = n / 2;
    let left_lim = (mid_row_i + 1).saturating_sub(k);
    let right_lim = mid_row_i.min(n - k);

    if left_lim > right_lim {
        return (0, n as u64);
    }

    let max_cover = right_lim - left_lim + 1;
    (max_cover, n as u64 - (max_cover as u64 - 1) * 2)
}

fn solve(row_count: usize, column_count: usize, k: usize, heights: Vec<u64>) -> u64 {
    let (row_max_cover, mid_row_freq) = get_max_cover(row_count, k);
    let (column_max_cover, mid_column_freq) = get_max_cover(column_count, k);

    let mut freqs = BTreeMap::<usize, u64>::new();
    freqs.insert(
        row_max_cover * column_max_cover,
        mid_row_freq * mid_column_freq,
    );

    for column_cover in 1..column_max_cover {
        *freqs.entry(row_max_cover * column_cover).or_insert(0) += mid_row_freq * 2;
    }

    for row_cover in 1..row_max_cover {
        *freqs.entry(column_max_cover * row_cover).or_insert(0) += mid_column_freq * 2;
    }

    for row_cover in 1..row_max_cover {
        for column_cover in 1..column_max_cover {
            *freqs.entry(row_cover * column_cover).or_insert(0) += 4;
        }
    }

    let mut heights = heights;
    heights.sort_by(|a, b| b.cmp(a));

    let mut spectacle = 0;

    for height in heights {
        let mut entry = freqs.last_entry().unwrap();
        spectacle += *entry.key() as u64 * height;
        *entry.get_mut() -= 1;
        if *entry.get() == 0 {
            entry.remove();
        }
    }

    spectacle
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let line: Vec<_> = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<usize>().unwrap())
            .collect();

        let row_count = line[0];
        let column_count = line[1];
        let k = line[2];

        lines.next();

        let seq = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<u64>().unwrap())
            .collect();

        println!("{}", solve(row_count, column_count, k, seq));
    }
}
