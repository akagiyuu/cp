use std::{
    collections::{BinaryHeap, HashMap},
    io,
};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

struct Meeting {
    start: i128,
    end: i128,
    index: i128,
}

fn main() {
    let mut lines = io::stdin().lines();
    let n = readline!(lines).parse::<i128>().unwrap();
    let mut meetings = vec![];
    for _ in 0..n {
        let a = readline!(lines)
            .split(", ")
            .map(|x| x.parse::<i128>().unwrap())
            .collect::<Vec<_>>();
        let meeting = Meeting {
            start: a[0],
            end: a[1],
            index: a[2],
        };
        meetings.push(meeting);
    }
    meetings.sort_by(|a, b| {
        if a.end == b.end {
            a.index.cmp(&b.index)
        } else {
            a.end.cmp(&b.end)
        }
    });

    let mut cur_time = -1;
    let mut result = vec![];

    for meeting in meetings {
        if meeting.start > cur_time {
            result.push(meeting.index);
            cur_time = meeting.end;
        }
    }

    println!("{}", result.len());
    for i in 0..result.len() {
        if i != 0 {
            print!(", ");
        }
        print!("{}", result[i]);
    }
    println!()
}
