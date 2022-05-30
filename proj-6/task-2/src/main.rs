use rand::Rng;
use std::fs::File;
use std::io::{stdin, BufRead, BufReader, BufWriter, Write};

#[derive(Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Point {
        Point { x, y }
    }

    fn read_from_file(filename: &str) -> Vec<Point> {
        let mut points = Vec::new();
        let file = BufReader::new(
            File::open(filename).unwrap_or_else(|_| panic!("Can't open file {}", filename)),
        );
        for line in file.lines() {
            let lt = line.unwrap();
            let mut l = lt.split_whitespace();
            let x: i32 = l.next().unwrap().parse().unwrap();
            let y: i32 = l.next().unwrap().parse().unwrap();
            points.push(Point::new(x, y));
        }
        points.push(points[0]);
        points
    }

    fn distance(p1: &Point, p2: &Point) -> f32 {
        (((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) as f32).sqrt()
    }

    fn path_distance(path: &[Point]) -> f32 {
        let mut distance = 0.0;
        for (i, x) in path.iter().enumerate().skip(1) {
            distance += Point::distance(x, &path[i - 1]);
        }
        distance
    }
}

fn main() {
    println!("Enter filename to read from:");
    let mut filename = String::new();
    stdin()
        .read_line(&mut filename)
        .expect("Couldn't read input");
    let filename = filename.trim_start().trim_end();

    let starting_path = Point::read_from_file(filename);
    println!(
        "Starting path distance: {}",
        Point::path_distance(&starting_path)
    );

    println!("Enter max number of iterations:");
    let mut buffer = String::new();
    stdin().read_line(&mut buffer).expect("Couldn't read input");
    let it_max = buffer.trim_start().trim_end().parse::<usize>().unwrap();

    let mut rng = rand::thread_rng();
    let mut path = starting_path;
    for i in (1..=100).rev() {
        for _ in 0..it_max {
            let b = rng.gen_range(1..(path.len() - 2));
            let c = rng.gen_range((b + 1)..(path.len() - 1));
            let mut new_path = path.clone();
            for j in b..=c {
                new_path[j] = path[c - j + b];
            }
            let old_distance = Point::path_distance(&path);
            let new_distance = Point::path_distance(&new_path);
            if new_distance < old_distance
                || rng.gen::<f32>()
                    < ((old_distance - new_distance) / (0.001 * i as f32 * i as f32)).exp()
            {
                path = new_path.to_vec();
            }
        }
    }

    println!("Minimized path distance: {}", Point::path_distance(&path));

    println!("Enter output filename:");
    let mut filename = String::new();
    stdin()
        .read_line(&mut filename)
        .expect("Couldn't read input");
    let filename = filename.trim_start().trim_end();

    let output =
        File::create(filename).unwrap_or_else(|_| panic!("Can't create file {}", filename));
    let mut output = BufWriter::new(output);

    for p in &path {
        writeln!(output, "{} {}", p.x, p.y)
            .unwrap_or_else(|_| panic!("Can't write to file {}", filename));
    }
}
