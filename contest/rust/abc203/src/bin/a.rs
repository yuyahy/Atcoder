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
        dice: [usize; 3],
    }
    //println!("{:?}", dice);

    let result = match &dice[..] {
        [a, b, c] if a == b => Some(c),
        [a, b, c] if b == c => Some(a),
        [a, b, c] if c == a => Some(b),
        _ => None,
    };

    match result {
        Some(value) => println!("{}", value),
        None => println!("0"),
    }
}
