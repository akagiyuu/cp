use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn get_count(choosen: &mut Vec<usize>, n: usize, freq: &mut Vec<usize>) -> usize {
    if choosen.len() == n {
        let mut count = 0;
        for i in 0..n  {
            for j in i..n {
                let min = *choosen.iter().skip(i).take(j - i + 1).min().unwrap();
                let max = *choosen.iter().skip(i).take(j - i + 1).max().unwrap();
                if max - min == j - i {
                    count += 1;
                }
            }
        }
        freq[choosen[0]] += count;
        // println!("{:?}: {}", choosen, count);
        return count;
    }

    let mut count = 0;
    for i in 0..n {
        if i == 2 {
            continue;
        }
        if choosen.contains(&i) {
            continue;
        }
        choosen.push(i);
        count += get_count(choosen, n, freq);
        choosen.pop();
    }

    count
}

fn factorial(n: usize) -> usize {
    (1..=n).product()
}

fn main() {
    for i in 3..=10 {
        let mut freq = vec![0; i];
        let mut choosen = vec![2];
        println!("{}", get_count(&mut choosen, i, &mut freq));
        println!("{:?}", freq);
    }
    // let mut lines = io::stdin().lines();
}
