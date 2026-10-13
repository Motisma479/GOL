pub fn enter_alter_screen()
{
    print!("\x1B[?1049h")
}

pub fn exit_alter_screen()
{
    print!("\x1B[?1049l")
}

pub fn move_cursor(x:i32, y:i32)
{
    print!("\x1B[{};{}H",x,y)
}