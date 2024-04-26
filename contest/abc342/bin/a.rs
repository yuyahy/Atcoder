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

#[fastout]
fn main() {
    input! {
        s: Chars,
    }

    // 文字の出現回数をカウント
    let mut char_counts = HashMap::new();
    for (index, ch) in s.iter().enumerate() {
        *char_counts.entry(ch).or_insert(0) += 1;
    }

    // 文字の出現回数が1の物を集めて配列にする(問題の制約により1個だけのはず)
    let indexes: Vec<usize> = s
        .iter()
        .enumerate()
        .filter_map(|(i, ch)| if char_counts[&ch] == 1 { Some(i) } else { None })
        .collect();

    println!("{:?}", indexes[0] + 1);
}
