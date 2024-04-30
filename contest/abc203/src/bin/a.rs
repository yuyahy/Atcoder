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
    let mut number_counter = HashMap::<usize, usize>::new();
    for a in dice {
        *number_counter.entry(a).or_insert(0) += 1;
    }
    // println!("{:?}", number_counter);

    if number_counter.len() == 1 {
        if let Some((number, _)) =
            number_counter.iter().next()
        {
            println!("{}", number);
        }
    } else if number_counter.len() == 2 {
        for (number, count) in number_counter {
            if count == 1 {
                println!("{}", number);
                break;
            }
        }
    } else {
        println!("{}", 0);
    }
}
