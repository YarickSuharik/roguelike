namespace RL;

public class World
{
    private readonly List<Actor> actors = new();
    private char[]? tileMap;
    private int mapWidth;
    private int mapHeight;

    public int Width => mapWidth;
    public int Height => mapHeight;

    public Camera? CameraContext { get; private set; }
    public PlayerCharacter? PlayerCharacter { get; private set; }

    // мир создаёт актёров сам, поэтому они не могут пережить мир
    public T SpawnActor<T>(Func<World, T> factory) where T : Actor
    {
        T actor = factory(this);
        actors.Add(actor);
        actor.OnSpawned();
        return actor;
    }

    public bool DestroyActor(Actor actor) => actors.Remove(actor);

    public void RegisterCamera(Camera camera) => CameraContext = camera;

    public void NotifyCameraRefresh() => CameraContext?.Refresh();

    public void SetPlayerCharacter(PlayerCharacter player) => PlayerCharacter = player;

    public bool InitializeMap(string[] lines)
    {
        if (lines.Length == 0) return false;

        mapHeight = lines.Length;
        mapWidth = lines.Max(line => line.Length);
        tileMap = new char[mapWidth * mapHeight];
        Array.Fill(tileMap, ' ');

        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < lines[y].Length; x++)
            {
                tileMap[y * mapWidth + x] = lines[y][x];
            }
        }

        return true;
    }

    public CellContent GetObjectOnPos(Position position)
    {
        if (tileMap is null) return new CellContent(true, null);
        if (!IsInsideMap(position)) return new CellContent(true, null);
        if (GetTile(position) != ' ') return new CellContent(true, null);

        return new CellContent(false, GetActorAt(position));
    }

    public bool CanMoveTo(Actor movingActor, Position targetPosition)
    {
        CellContent content = GetObjectOnPos(targetPosition);

        if (content.IsWall) return false;

        if (content.Actor is not null
            && !ReferenceEquals(content.Actor, movingActor)
            && content.Actor.OnCollisionEvent())
        {
            return false;
        }

        return true;
    }

    public char GetTile(Position position) =>
        IsInsideMap(position) && tileMap is not null
            ? tileMap[position.Y * mapWidth + position.X]
            : ' ';

    private bool IsInsideMap(Position position) =>
        position.X >= 0 && position.X < mapWidth && position.Y >= 0 && position.Y < mapHeight;

    private Actor? GetActorAt(Position position) =>
        actors.FirstOrDefault(actor => actor.Location.X == position.X && actor.Location.Y == position.Y);
}
