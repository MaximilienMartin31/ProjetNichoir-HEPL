using Microsoft.EntityFrameworkCore;
using WebApplication1.Models;

namespace WebApplication1
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Capture> Captures { get; set; }
        public DbSet<Album> Albums { get; set; }
        public DbSet<Album_Capture> Albums_Captures { get; set; } // Ta table de lien

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // 1. Définition de la clé primaire composée
            modelBuilder.Entity<Album_Capture>()
                .HasKey(ac => new { ac.id_album, ac.id_capture });

            // 2. Configuration des relations avec Suppression en Cascade
            modelBuilder.Entity<Album_Capture>()
                .HasOne(ac => ac.Album)
                .WithMany(al => al.Album_Captures)
                .HasForeignKey(ac => ac.id_album)
                .OnDelete(DeleteBehavior.Cascade); 

            modelBuilder.Entity<Album_Capture>()
                .HasOne(ac => ac.Capture)
                .WithMany(c => c.Album_Captures)
                .HasForeignKey(ac => ac.id_capture)
                .OnDelete(DeleteBehavior.Cascade); 

            // Mapping des noms de tables
            modelBuilder.Entity<Capture>().ToTable("Capture");
            modelBuilder.Entity<Album>().ToTable("Albums");
            modelBuilder.Entity<Album_Capture>().ToTable("Albums_Captures");
        }
    }
}
