using System.ComponentModel.DataAnnotations.Schema;

namespace WebApplication1.Models
{
    public class Album_Capture
    {
        // Clé composite ou Clé primaire simple selon tes préférences
        // Ici on suit strictement ton schéma avec les deux FK

        public int id_album { get; set; }
        [ForeignKey("id_album")]
        public Album? Album { get; set; }

        public int id_capture { get; set; }
        [ForeignKey("id_capture")]
        public Capture? Capture { get; set; }
    }
}
