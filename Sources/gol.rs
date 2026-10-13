use bit_set::BitSet;
use std::time::Instant;
use std::time::Duration;
use crate::terminal;

pub struct GOL
{
    width: i64,
    height: i64,
    data: BitSet,
    restricted: bool,
    has_changed: bool,
    last_update: Instant
}

impl GOL
{
    pub fn new(width: i64, height: i64) -> Self
    {
        let gol = Self
        {
            width,
            height,
            data: BitSet::with_capacity((width*height) as usize),
            restricted: false,
            has_changed: true,
            last_update: Instant::now()
        };
        gol
        // gol.data.remove(305); 
    }

    pub fn update(&mut self, delay:u64)
    {
        let now = Instant::now();
        if self.last_update + Duration::from_millis(delay) < now
        {
            let mut data_copy = self.data.clone();
            
            for y in 0..self.height
            {
                for x in 0..self.width
                {
                    if self.update_cell(x,y) != self.data.contains((x+y*self.width)as usize)
                    {
                        let n = (x+y*self.width)as usize;
                        if data_copy.contains(n)
                        {
                            data_copy.remove(n); 
                        } else
                        {
                            data_copy.insert(n); 
                        }
                    }
                }
            }
            
            self.data = data_copy;
            self.last_update = now;
        }
    }

    pub fn print(&mut self)
    {
        if self.has_changed
        {
            
            terminal::move_cursor(0,0);
            
            // let data_copy = self.data.clone();
            for y in 0..self.height
            {
                for x in 0..self.width
                {
                    let v = if self.data.contains((x+y*self.width)as usize)
                    {
                        "\x1B[48;2;0;0;0m  "
                    } else
                    {
                        "\x1B[48;2;255;255;255m  "
                    };
                    print!("{}",v);
                }
                print!("\n");
            }
            self.has_changed = false;
        }
    }
        
    pub fn change_cell(&mut self, x:i64, y:i64)
    {
        let n = (x+y*self.width)as usize;
        if self.data.contains(n)
        {
            self.data.remove(n); 
        } else
        {
            self.data.insert(n); 
        }
    }

    fn get_value(&self, x:i64, y:i64)->u32
    {
        if self.restricted
        {
            if x < 0 || x >= self.width-1  {return 0;}
            if y < 0 || y >= self.height-1 {return 0;}
            return if self.data.contains((x+y*self.width)as usize) {1} else {0};
        }
        else
        {
            let mut x_valid = x;
            let mut y_valid = y;
            if x < 0 {x_valid += self.width;}
            if y < 0 {y_valid += self.height;}
            if x > self.width-1  {x_valid -= self.width;}
            if y > self.height-1 {y_valid -= self.height;}
            return if self.data.contains((x_valid+y_valid*self.width)as usize) {1} else {0};
        }
    }

    fn update_cell(&mut self, x:i64, y:i64)->bool
    {
        let mut living_arround = 0;

        living_arround += self.get_value(x-1,y+1);
        living_arround += self.get_value(x,y+1);
        living_arround += self.get_value(x+1,y+1);
        living_arround += self.get_value(x-1,y);

        living_arround += self.get_value(x+1,y);
        living_arround += self.get_value(x-1,y-1);
        living_arround += self.get_value(x,y-1);
        living_arround += self.get_value(x+1,y-1);

        if self.data.contains((x+y*self.width)as usize)
        {
            if living_arround<2 || living_arround>3
            {
                self.has_changed = true;
                return false;
            }
        }
        else
        {
            if living_arround==3
            {
                self.has_changed = true;
                return true;
            }
        }
        return self.data.contains((x+y*self.width)as usize);
    }
}