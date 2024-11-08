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
        let seq: Vec<_> = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<u32>().unwrap())
            .collect();

        let mut prefix_xor = vec![0; seq.len()];
        prefix_xor[0] = seq[0];
        for i in 1..seq.len() {
            prefix_xor[i] = prefix_xor[i - 1] ^ seq[i];
        }

        for _ in 0..q {
            let line = readline!(lines);
            let (l, r) = line.split_once(' ').unwrap();
            let l: usize = l.parse().unwrap();
            let l = l - 1;
            let r: usize = r.parse().unwrap();
            let r = r - 1;
            let total_xor = prefix_xor[r] ^ if l == 0 { 0 } else { prefix_xor[l - 1] };
            if total_xor == 0 {
                println!("YES");
                continue;
            }

            let mut partial_xor = 0;
            let mut first_comp_end = l;
            while first_comp_end <= r {
                partial_xor ^= seq[first_comp_end];
                if partial_xor == total_xor {
                    break;
                }
                first_comp_end += 1;
            }

            let mut partial_xor = 0;
            let mut third_comp_start = r;
            while third_comp_start > first_comp_end {
                partial_xor ^= seq[third_comp_start];
                if partial_xor == total_xor {
                    break;
                }

                third_comp_start -= 1;
            }

            if partial_xor != total_xor {
                println!("NO");
                continue;
            }

            println!("YES");
        }
        println!()
    }
}
