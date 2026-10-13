mod terminal;
mod gol;

use crossterm::event::{self, Event, KeyCode};
use std::time::Duration;

fn main() -> Result<(), Box<dyn std::error::Error>>
{
    let mut gol_game = gol::GOL::new(48,32);

    gol_game.change_cell(4+1, 4);
    gol_game.change_cell(4+2, 4+1);
    gol_game.change_cell(4, 4+2);
    gol_game.change_cell(4+1, 4+2);
    gol_game.change_cell(4+2, 4+2);


    gol_game.change_cell(12+1, 9);
    gol_game.change_cell(12, 9+1);
    gol_game.change_cell(12+2, 9+1);
    gol_game.change_cell(12, 9+2);
    gol_game.change_cell(12+2, 9+2);
    gol_game.change_cell(12, 9+3);
    gol_game.change_cell(12+2, 9+3);
    gol_game.change_cell(12+1, 9+4);

    gol_game.change_cell(15+1, 9);
    gol_game.change_cell(15, 9+1);
    gol_game.change_cell(15+2, 9+1);
    gol_game.change_cell(15, 9+2);
    gol_game.change_cell(15+2, 9+2);
    gol_game.change_cell(15, 9+3);
    gol_game.change_cell(15+2, 9+3);
    gol_game.change_cell(15+1, 9+4);

    gol_game.change_cell(19, 7);
    gol_game.change_cell(20, 7);
    gol_game.change_cell(21, 7);

    terminal::enter_alter_screen();
    // while !event::poll(Duration::ZERO)? 
    // {
    //     gol_game.update(500);
    //     gol_game.print();
    // }

    loop {
        if event::poll(Duration::from_millis(10))? {
            if let Event::Key(key) = event::read()? {
                if key.code ==  KeyCode::Esc
                {
                    break;
                }
            }
        }

        gol_game.update(120);
        gol_game.print();
    }

    terminal::exit_alter_screen();
    Ok(())
}
