use std::io::{self, BufRead};

fn into_vec(line: String) -> Vec<u32> {
    line.split(' ').map(|n| n.parse().unwrap()).collect()
}

fn main() -> io::Result<()> {
    let mut lines = io::stdin().lock().lines();

    while let Some(line) = lines.next() {
        let line = line?;
        println!("input: {:?}", into_vec(line));
    }

    Ok(())
}
