use std::io::{self, BufRead};

fn main() {
    let mut lines = io::stdin().lock().lines();
    lines.next();
    let mut fibonacci = [0usize; 200000];
    fibonacci[1] = 1;
    fibonacci[2] = 1;
    let mut highest_cached = 2;
    while let Some(input) = lines.next() {
        let input = input.unwrap();
        let mut input = input.split_whitespace();
        let n: usize = input.next().unwrap().parse().unwrap();
        let k: usize = input.next().unwrap().parse().unwrap();

        while highest_cached < k {
            highest_cached += 1;
            fibonacci[highest_cached] =
                fibonacci[highest_cached - 1].wrapping_add(fibonacci[highest_cached - 2]);
        }
        let mut count: u32 = 0;
        let f_0 = fibonacci[k];
        let f_1 = fibonacci[k - 1];
        let f_2 = fibonacci[k - 2];
        let lower_bound = ((n - 1) / f_0) + 1;
        let upper_bound = n / f_1;
        for i in 0..=n/f_0 {
            if (n - f_2 * i) % f_1 == 0 {
                count += 1;
            }
        }
        println!("{}", count);
    }
}
