using System.Text;

namespace RL;

public sealed class MapSource : IDisposable
{
    private readonly StreamReader reader;
    private bool disposed;

    public MapSource(string path)
    {
        reader = new StreamReader(path, Encoding.UTF8);
    }

    public string[] ReadAllLines()
    {
        var lines = new List<string>();
        string? line;

        while ((line = reader.ReadLine()) is not null)
        {
            lines.Add(line);
        }

        return lines.ToArray();
    }

    public void Dispose()
    {
        if (disposed) return;

        disposed = true;
        reader.Dispose();
        Console.WriteLine("[MapSource] map file closed and released");
    }
}
