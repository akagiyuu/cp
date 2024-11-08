use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(n: i64, d12: i64, d23: i64, d31: i64) {
    let n = n as usize;
    let a = d12 + d31 - d23;
    if a < 0 || a % 2 != 0 {
        println!("NO");
        return;
    }
    let a = a as usize / 2;

    let b = d12 + d23 - d31;
    if b < 0 || b % 2 != 0 {
        println!("NO");
        return;
    }
    let b = b as usize / 2;

    let c = d23 + d31 - d12;
    if c < 0 || c % 2 != 0 {
        println!("NO");
        return;
    }
    let c = c as usize / 2;

    if a + b + c > n - 1 || a + b + c < 2 || [a, b, c].iter().filter(|&&x| x == 0).count() > 1 {
        println!("NO");
        return;
    }

    println!("YES");
    if a != 0 && b != 0 && c != 0 {
        let parent_node = a + b + c + 1;

        let mut pre = 1;
        for i in 4..=a + 2 {
            println!("{} {}", pre, i);
            pre = i;
        }
        println!("{} {}", pre, parent_node);

        pre = 2;
        for i in a + 3..=a + b + 1 {
            println!("{} {}", pre, i);
            pre = i;
        }
        println!("{} {}", pre, parent_node);

        pre = 3;
        for i in a + b + 2..=a + b + c {
            println!("{} {}", pre, i);
            pre = i;
        }
        println!("{} {}", pre, parent_node);

        pre = parent_node;
        for i in parent_node + 1..=n {
            println!("{} {}", pre, i);
            pre = i;
        }
        return;
    }

    let parent_node = [a, b, c].into_iter().position(|x| x == 0).unwrap() + 1;
    let child_nodes: Vec<_> = [1, 2, 3]
        .into_iter()
        .filter(|&x| x != parent_node)
        .collect();
    let child_node_lengths: Vec<_> = [a, b, c].into_iter().filter(|&x| x != 0).collect();

    let mut node = 4;
    for i in 0..2 {
        let mut pre = child_nodes[i];
        for _ in 0..child_node_lengths[i] - 1 {
            println!("{} {}", pre, node);
            pre = node;
            node += 1;
        }
        println!("{} {}", pre, parent_node);
    }

    while node <= n {
        println!("{} {}", parent_node, node);
        node += 1;
    }
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count: usize = readline!(lines).parse().unwrap();
    for _ in 0..test_case_count {
        let a: Vec<_> = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<i64>().unwrap())
            .collect();
        solve(a[0], a[1], a[2], a[3]);
    }
}
