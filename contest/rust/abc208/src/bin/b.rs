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
       mut P: i64,
    }

    // 考察メモ
    // - 最小枚数にするには大きい硬貨から使うべき
    // <コインの種類の階乗、残り枚数>
    let mut coin_cnt: Vec<(i64, i64)> = Vec::new();
    for i in 1..=10 {
        //coin_map.insert((1..=i).product(), 100);
        coin_cnt.push(((1..=i).product(), 100));
    }
    // println!("{:?}", coin_cnt);
    coin_cnt.reverse();
    // println!("{:?}", coin_cnt);

    let mut result = 0;
    while P != 0 {
        // ムーブを参照で防ぐ
        for i in &coin_cnt {
            let quotient = P / i.0;
            if quotient == 0 {
                continue;
            }
            P -= std::cmp::min(quotient, 100) * i.0;
            result += std::cmp::min(quotient, 100);
        }
    }
    println!("{}", result);
}
