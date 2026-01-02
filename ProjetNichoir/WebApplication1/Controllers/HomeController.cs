using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Diagnostics;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly ApplicationDbContext _context;

        public HomeController(ILogger<HomeController> logger,ApplicationDbContext context)
        {
            _logger = logger;
            _context = context;
        }

        public IActionResult Index()
        {
            var viewModel = new HomeViewModel
            {
                // 5 dernières photos
                DernieresCaptures = _context.Captures
                    .OrderByDescending(c => c.date_capture)
                    .Take(5)
                    .ToList(),

                // Les favoris
                Favoris = _context.Captures
                    .Where(c => c.favoris == true)
                    .OrderByDescending(c => c.date_capture)
                    .Take(5)
                    .ToList(),

                // La liste des albums
                Albums = _context.Albums.ToList()
            };

            ViewBag.Battery = viewModel.DernieresCaptures
                 .OrderByDescending(c => c.date_capture)
                 .FirstOrDefault()?.batterie;

            return View(viewModel);
        }
        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

        #region Phototheque
        public IActionResult Phototheque()
        {
            var viewModel = new HomeViewModel
            {
                // 5 dernières photos
                DernieresCaptures = _context.Captures
                    .OrderByDescending(c => c.date_capture)
                    .ToList(),

                // Les favoris
                Favoris = _context.Captures
                    .Where(c => c.favoris == true)
                    .OrderByDescending(c => c.date_capture)
                    .ToList(),

                // La liste des albums
                Albums = _context.Albums.ToList()

                
            };

            return View(viewModel);
        }
        [HttpGet]
        public IActionResult PhotothequeFilter(string? type, string mode,DateTime? date, DateTime? start, DateTime? end)
        {
            var query = _context.Captures.AsQueryable();

            if (type == "favorites")
            {
                query = query.Where(c => c.favoris == true);
            }
            else if (type == "date_mode")
            {
                if (mode == "precise")
                {
                    query = query.Where(c => c.date_capture.Date == date.Value.Date);
                }
                else if (mode == "range")
                {
                    query = query.Where(c => c.date_capture >= start.Value && c.date_capture <= end.Value.AddDays(1));
                }
            }

            var viewModel = new HomeViewModel
            {
                DernieresCaptures = query.ToList(),
                Albums = _context.Albums.ToList(),
                Favoris = _context.Captures
                    .Where(c => c.favoris == true)
                    .ToList(),
            };

            ViewBag.FilterType = type;
            ViewBag.FilterMode = mode;
            ViewBag.FilterDate = date?.ToString("yyyy-MM-dd");
            ViewBag.FilterStart = start?.ToString("yyyy-MM-dd");
            ViewBag.FilterEnd = end?.ToString("yyyy-MM-dd");
            return View("Phototheque", viewModel);
        }
        [HttpPost]
        public IActionResult ToggleFavorite(int id) 
        {
            var photo = _context.Captures.Find(id);
            if (photo != null)
            {
                photo.favoris = !photo.favoris;

                _context.Captures.Update(photo);
                _context.SaveChanges();
            }
            return Ok();
        }
        [HttpPost]
        public IActionResult AddToAlbum(int albumId, string selectedPhotoIds)
        {
            if (string.IsNullOrEmpty(selectedPhotoIds))
            {
                return RedirectToAction("Phototheque");
            }

            var photoIdList = selectedPhotoIds
                .Split(',')
                .Select(int.Parse)
                .ToList();

            try
            {
                // 2. Logique d'insertion en base de données
                foreach (var photoId in photoIdList)
                {
                    Album_Capture album_Capture = new Album_Capture { id_album = albumId, id_capture = photoId };

                    _context.Albums_Captures.Add(album_Capture);
                }

                 _context.SaveChanges(); 

            }
            catch (Exception ex)
            {
                TempData["Error"] = "Une erreur est survenue lors de l'ajout.";
            }

            return RedirectToAction("Phototheque");
        }
        [HttpPost]
        public IActionResult AddFavoritesBulk(string selectedPhotoIds)
        {
            if (!string.IsNullOrEmpty(selectedPhotoIds))
            {
                var idList = selectedPhotoIds.Split(',').Select(int.Parse).ToList();

                try
                {

                    foreach (var id in idList)
                    {
                        Capture cap = _context.Captures.First(cp=>cp.id_capture == id);

                        cap.favoris = true;

                        _context.Captures.Update(cap);
                        _context.SaveChanges();
                    }

                    TempData["Success"] = "Sélection ajoutée aux favoris.";
                }
                catch (Exception)
                {
                    TempData["Error"] = "Erreur lors de la mise à jour des favoris.";
                }
            }

            return RedirectToAction("Phototheque");
        }
        [HttpPost]
        public IActionResult DeletePhotosBulk(string selectedPhotoIds)
        {
            if (!string.IsNullOrEmpty(selectedPhotoIds))
            {
                var idList = selectedPhotoIds.Split(',').Select(int.Parse).ToList();

                try
                {
                    foreach (var id in idList)
                    {
                        // 1. Récupérer les infos de la capture (pour avoir le chemin du fichier)
                        var capture = _context.Captures.First(cp=> cp.id_capture == id);

                        if (capture != null)
                        {
                            if (System.IO.File.Exists(capture.chemin_image))
                            {
                                try
                                {
                                    System.IO.File.Delete(capture.chemin_image);
                                }
                                catch (Exception ex)
                                {
                                }
                            }

                            // 3. Supprimer de la base de données
                            _context.Captures.Remove(capture);
                            _context.SaveChanges();
                        }
                    }
                    TempData["Success"] = "La sélection a été supprimée.";
                }
                catch (Exception ex)
                {
                    TempData["Error"] = "Erreur lors de la suppression de certains éléments.";
                }
            }

            return RedirectToAction("Phototheque");
        }
        #endregion

        #region Album
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult CreateAlbum(string nom)
        {
            nom = (nom ?? "").Trim();

            var album = new Album
            {
                nom = nom
            };

            _context.Albums.Add(album);
            _context.SaveChanges();



            return RedirectToAction(nameof(Index));
        }
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult EditAlbum(int id, string nom)
        {
            nom = (nom ?? "").Trim();

            var album = _context.Albums.First(a => a.id_album == id);
            album.nom = nom;

            _context.Update(album);
            _context.SaveChanges();

            return RedirectToAction(nameof(Index));
        }
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult DeleteAlbum(int id)
        {

            var album = _context.Albums.First(a => a.id_album == id);

            _context.Remove(album);
            _context.SaveChanges();

            return RedirectToAction(nameof(Index));
        }

        #endregion

        #region Photo par album
        public IActionResult PhotosParAlbum(int id)
        {
            ViewBag.Nom = _context.Albums.FirstOrDefault(al => al.id_album == id).nom;
            // 1. Récupérer uniquement les IDs des captures liées à CET album spécifique
            var captureIds = _context.Albums_Captures
                .Where(ac => ac.id_album == id)
                .Select(ac => ac.id_capture)
                .ToList();

            // 2. Récupérer les détails de ces captures
            List<Capture> capturesAlbum = _context.Captures
                .Where(cp => captureIds.Contains(cp.id_capture))
                .ToList();

            // 3. Récupérer les favoris (en supposant qu'il y a un champ booléen 'IsFavori')
            List<Capture> mesFavoris = _context.Captures
                .Where(cp => cp.favoris == true) // Adaptez le nom de la colonne si nécessaire
                .ToList();

            // 4. Intégrer au ViewModel
            var viewModel = new HomeViewModel
            {
                DernieresCaptures = capturesAlbum,
                Favoris = mesFavoris,
                Albums = _context.Albums.ToList()
            };

            return View(viewModel);
        }
        #endregion

        #region Photo favoris
        public IActionResult Photofavoris()
        {
            ViewBag.Nom = "Favoris";


            var viewModel = new HomeViewModel
            {
                // 5 dernières photos
                DernieresCaptures = _context.Captures
                    .Where(c => c.favoris == true)
                    .OrderByDescending(c => c.date_capture)
                    .ToList()
,



            };

            return View("PhotosParAlbum", viewModel);
        }

        #endregion

    }
}
