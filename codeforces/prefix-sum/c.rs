use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn map(c: u8) -> usize {
    (c - b'a') as usize
}

fn solve(s: &str) -> u32 {
    let n = s.len();
    if n == 1 {
        return 1;
    }

    let mut freq_odd = vec![[0; 26]; n];
    let mut freq_even = vec![[0; 26]; n];
    freq_even[0][map(s.as_bytes()[0])] = 1;

    for i in 1..n {
        freq_even[i] = freq_even[i - 1];
        freq_odd[i] = freq_odd[i - 1];
        if i % 2 == 0 {
            freq_even[i][map(s.as_bytes()[i])] += 1;
        } else {
            freq_odd[i][map(s.as_bytes()[i])] += 1;
        }
    }

    if n % 2 == 0 {
        return n as u32
            - *freq_odd[n - 1].iter().max().unwrap()
            - *freq_even[n - 1].iter().max().unwrap();
    }

    let mut min_operation = u32::MAX;

    for i in 0..n {
        let odd_left = if i == 0 { [0; 26] } else { freq_odd[i - 1] };

        let max_odd = (0..26)
            .map(|j| odd_left[j] + freq_even[n - 1][j] - freq_even[i][j])
            .max()
            .unwrap();

        let even_left = if i == 0 { [0; 26] } else { freq_even[i - 1] };
        let mut even_right = freq_odd[n - 1];
        if i % 2 == 1 {
            even_right[map(s.as_bytes()[i])] -= 1;
        }

        let max_even = (0..26)
            .map(|j| even_left[j] + freq_odd[n - 1][j] - freq_odd[i][j])
            .max()
            .unwrap();

        let operation = n as u32 - max_odd - max_even;
        min_operation = min_operation.min(operation);
    }

    min_operation
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        lines.next();
        let s = readline!(lines);
        println!("{}", solve(&s));
    }
}
