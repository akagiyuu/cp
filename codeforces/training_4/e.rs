use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

#[derive(Debug)]
struct Person {
    x: u64,
    y: u64,
}

fn contain_value_in_range(a: &[u64], left: u64, right: u64) -> Option<usize> {
    let mut i = 0;
    let mut j = a.len() - 1;
    while i < j {
        let mid = (i + j) / 2;
        let value = a[mid];
        if value >= right {
            j = if mid == 0 { 0 } else { mid - 1 };
        } else if value <= left {
            i = mid + 1;
        } else {
            return Some(mid);
        }
    }

    if i < a.len() && a[i] > left && a[i] < right {
        Some(i)
    } else {
        None
    }
}

fn solve_vertical_people(streets_y: &[u64], people: &[Person]) -> u64 {
    let mut convinient_count = 0;
    let people_count = people.len();

    for i in 0..people_count {
        for j in i + 1..people_count {
            if people[i].x == people[j].x {
                convinient_count += 1;
                continue;
            }

            let y1 = people[i].y;
            let y2 = people[j].y;
            if y1 == y2 {
                continue;
            }

            let min_y = y1.min(y2);
            let max_y = y1.max(y2);

            if contain_value_in_range(streets_y, min_y, max_y).is_some() {
                convinient_count += 1;
            }
        }
    }

    convinient_count
}

fn solve_horizontal_people(streets_x: &[u64], people: &[Person]) -> u64 {
    let mut convinient_count = 0;
    let people_count = people.len();
    for i in 0..people_count {
        for j in i + 1..people_count {
            if people[i].y == people[j].y {
                convinient_count += 1;
                continue;
            }

            let x1 = people[i].x;
            let x2 = people[j].x;
            if x1 == x2 {
                continue;
            }

            let min_x = x1.min(x2);
            let max_x = x1.max(x2);

            if contain_value_in_range(streets_x, min_x, max_x).is_some() {
                convinient_count += 1;
            }
        }
    }
    convinient_count
}

fn solve(
    streets_x: Vec<u64>,
    streets_y: Vec<u64>,
    vertical_people: Vec<Person>,
    horizontal_people: Vec<Person>,
) -> u64 {
    let convinient_count = solve_vertical_people(&streets_y, &vertical_people)
        + solve_horizontal_people(&streets_x, &horizontal_people)
        + vertical_people.len() as u64 * horizontal_people.len() as u64;
    let people_count = vertical_people.len() as u64 + horizontal_people.len() as u64;

    people_count * (people_count - 1) / 2 - convinient_count
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let people_count = readline!(lines)
            .split_ascii_whitespace()
            .nth(2)
            .unwrap()
            .parse::<u64>()
            .unwrap();

        let streets_x = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<u64>().unwrap())
            .collect::<Vec<_>>();
        let streets_y = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<u64>().unwrap())
            .collect::<Vec<_>>();
        let mut vertical_people = vec![];
        let mut horizontal_people = vec![];
        for i in 0..people_count {
            let line = readline!(lines);
            let (x, y) = line.split_once(' ').unwrap();
            let x = x.parse::<u64>().unwrap();
            let y = y.parse::<u64>().unwrap();
            let is_vertical = streets_x.binary_search(&x).is_ok();
            let is_horizontal = streets_y.binary_search(&y).is_ok();
            if is_vertical && is_horizontal {
                continue;
            }
            let person = Person { x, y };
            if is_vertical {
                vertical_people.push(person);
            } else {
                horizontal_people.push(person);
            }
        }

        println!(
            "{}",
            solve(streets_x, streets_y, vertical_people, horizontal_people)
        );
    }
}
