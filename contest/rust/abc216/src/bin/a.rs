#[allow(unused_imports)]
use itertools::{iproduct, Itertools};
#[allow(unused_imports)]
use num_traits::pow;
#[allow(unused_imports)]
use proconio::{
    fastout, input,
    marker::{Chars, Usize1},
};
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::{HashMap, HashSet, VecDeque};
#[allow(unused_imports)]
use std::iter::FromIterator;
#[allow(non_snake_case)]
#[fastout]
fn main() {
    input! {
        //X: usize, Y: usize,
        input: String,
    }
    // 考察メモ

    // 指定文字で区切り、Vecに格納する
    let parts: Vec<&str> = input.split('.').collect();

    // parse()を使うと文字列を任意の型に変換する事ができる
    // parseはResult型を返すので、unwrap()を使うと値が存在すればそのまま取得、しなければpanicが発生する
    // →実際のアプリケーションではunwrap()ではなく、パターンマッチングなどでエラーハンドリングするべき
    let X = parts[0].parse::<i64>().unwrap();
    let Y: i64 =
        parts[1].parse().expect("This is not a number!!!");

    match Y {
        // y if 0 <= y && y <= 2 => println!("{}-", X),
        // y if 3 <= y && y <= 6 => println!("{}", X),
        // _ => println!("{}+", X),
        y if (0..=2).contains(&y) => println!("{}-", X),
        y if (3..=6).contains(&y) => println!("{}", X),
        _ => println!("{}+", X),
    }
}
