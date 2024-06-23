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
        N: usize, K: usize,
    }
    // println!("N : {:?}", N);
    // println!("K : {:?}", K);

    // N * (1...K)
    let mut result: i64 = 0;
    for n in 0..N {
        for k in 0..K {
            let room_number =
                format!("{}0{}", n + 1, k + 1);
            // println!("{:?}", room_number);
            result += room_number.parse::<i64>().unwrap();
        }
    }
    println!("{:?}", result);
}
