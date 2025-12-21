using System.ComponentModel.DataAnnotations;

namespace WebApplication1.Models
{
    public class Album
    {
        [Key]
        public int id_album { get; set; }
        public string nom { get; set; }

        // Relation Many-to-Many avec Captures
        public virtual ICollection<Album_Capture>? Album_Captures { get; set; } = new List<Album_Capture>();
    }
}
