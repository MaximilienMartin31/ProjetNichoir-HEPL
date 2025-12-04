using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using ProjetNichoir.Data;
using ProjetNichoir.Models;

namespace ProjetNichoir.Controllers
{
    public class CapturesController : Controller
    {
        private readonly ApplicationDbContext _context;

        public CapturesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: Captures
        public async Task<IActionResult> Index()
        {
            var applicationDbContext = _context.Captures.Include(c => c.nichoir);
            return View(await applicationDbContext.ToListAsync());
        }

        // GET: Captures/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var capture = await _context.Captures
                .Include(c => c.nichoir)
                .FirstOrDefaultAsync(m => m.id_capture == id);
            if (capture == null)
            {
                return NotFound();
            }

            return View(capture);
        }

        // GET: Captures/Create
        public IActionResult Create()
        {
            ViewData["id_nichoir"] = new SelectList(_context.Nichoirs, "id_nichoir", "nom");
            return View();
        }

        // POST: Captures/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("id_capture,id_nichoir,chemin_image,date_capture,taille_image,batterie,resolution")] Capture capture)
        {
            if (ModelState.IsValid)
            {
                _context.Add(capture);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            ViewData["id_nichoir"] = new SelectList(_context.Nichoirs, "id_nichoir", "nom", capture.id_nichoir);
            return View(capture);
        }

        // GET: Captures/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var capture = await _context.Captures.FindAsync(id);
            if (capture == null)
            {
                return NotFound();
            }
            ViewData["id_nichoir"] = new SelectList(_context.Nichoirs, "id_nichoir", "nom", capture.id_nichoir);
            return View(capture);
        }

        // POST: Captures/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("id_capture,id_nichoir,chemin_image,date_capture,taille_image,batterie,resolution")] Capture capture)
        {
            if (id != capture.id_capture)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(capture);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!CaptureExists(capture.id_capture))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            ViewData["id_nichoir"] = new SelectList(_context.Nichoirs, "id_nichoir", "nom", capture.id_nichoir);
            return View(capture);
        }

        // GET: Captures/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var capture = await _context.Captures
                .Include(c => c.nichoir)
                .FirstOrDefaultAsync(m => m.id_capture == id);
            if (capture == null)
            {
                return NotFound();
            }

            return View(capture);
        }

        // POST: Captures/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var capture = await _context.Captures.FindAsync(id);
            if (capture != null)
            {
                _context.Captures.Remove(capture);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool CaptureExists(int id)
        {
            return _context.Captures.Any(e => e.id_capture == id);
        }
    }
}
