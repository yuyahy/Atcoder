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
        s: String,
    }
    // println!("{:?}", s);

    let s: Vec<char> = s.chars().collect();

    let s_conv: String = s
        .iter()
        .rev()
        .map(|&ch| match ch {
            '6' => '9',
            '9' => '6',
            _ => ch,
        })
        .collect();

    println!("{}", s_conv);
}
