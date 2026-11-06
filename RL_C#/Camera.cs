using System.Text;

namespace RL;

public class Camera
{
    private readonly World world;

    public Position Location { get; set; }
    public int Width { get; }
    public int Height { get; }
    public Actor? TrackedActor { get; set; }

    public Camera(Position startPosition, int width, int height, World worldContext)
    {
        Location = startPosition;
        Width = width;
        Height = height;
        world = worldContext;
    }

    public void Refresh()
    {
        int startX = Location.X;
        int startY = Location.Y;

        if (TrackedActor is not null)
        {
            startX = TrackedActor.Location.X - Width / 2;
            startY = TrackedActor.Location.Y - Height / 2;
        }

        var buffer = new char[Height, Width];

        for (int y = 0; y < Height; y++)
        {
            for (int x = 0; x < Width; x++)
            {
                var position = new Position(startX + x, startY + y);
                CellContent content = world.GetObjectOnPos(position);
                buffer[y, x] = content.Actor?.Symbol ?? world.GetTile(position);
            }
        }

        var builder = new StringBuilder();
        for (int y = 0; y < Height; y++)
        {
            for (int x = 0; x < Width; x++)
            {
                builder.Append(buffer[y, x]);
            }
            builder.Append('\n');
        }

        try
        {
            Console.Clear();
        }
        catch (IOException)
        {
            // при перенаправленном выводе очистка консоли недоступна
        }

        Console.Write(builder.ToString());
    }
}
