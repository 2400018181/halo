// ===== DATA STRUCTURES =====
let transactions = [];
let customers = [];
let historyStack = [];
let currentService = 'baju';
let nextTransactionId = 1;

// ===== INITIALIZATION =====
document.addEventListener('DOMContentLoaded', () => {
    loadFromLocalStorage();
    initializeNavigation();
    initializeServiceTabs();
    initializeTransactionForm();
    updateDashboard();
    renderHistory();
    renderCustomers();
    updateCurrentDate();
    renderServiceInputs();
});

// ===== NAVIGATION =====
function initializeNavigation() {
    const navLinks = document.querySelectorAll('.nav-link');
    navLinks.forEach(link => {
        link.addEventListener('click', (e) => {
            e.preventDefault();
            const page = link.dataset.page;
            switchPage(page);
        });
    });
}

function switchPage(pageName) {
    // Update nav links
    document.querySelectorAll('.nav-link').forEach(link => {
        link.classList.remove('active');
    });
    document.querySelector(`[data-page="${pageName}"]`).classList.add('active');

    // Update pages
    document.querySelectorAll('.page').forEach(page => {
        page.classList.remove('active');
    });
    document.getElementById(pageName).classList.add('active');
}

// ===== SERVICE TABS =====
function initializeServiceTabs() {
    const tabs = document.querySelectorAll('.service-tab');
    tabs.forEach(tab => {
        tab.addEventListener('click', () => {
            tabs.forEach(t => t.classList.remove('active'));
            tab.classList.add('active');
            currentService = tab.dataset.service;
            renderServiceInputs();
            calculateTotal();
        });
    });
}

function renderServiceInputs() {
    const container = document.getElementById('service-inputs');

    const serviceConfigs = {
        baju: {
            html: `
                <div class="form-group">
                    <label>Berat (Kg)</label>
                    <input type="number" id="weight" step="0.1" min="0" placeholder="0.0" oninput="calculateTotal()">
                    <small>Harga: Rp 10.000/kg. Diskon 10% per kelipatan 10kg.</small>
                </div>
            `
        },
        selimut: {
            html: `
                <div class="form-grid">
                    <div class="form-group">
                        <label>Ukuran Selimut</label>
                        <select id="type" onchange="calculateTotal()">
                            <option value="15000">Selimut Bayi - Rp 15.000</option>
                            <option value="30000">Single Bed - Rp 30.000</option>
                            <option value="45000">Double Bed - Rp 45.000</option>
                            <option value="60000">Queen Bed - Rp 60.000</option>
                            <option value="75000">King Bed - Rp 75.000</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Jumlah (pcs)</label>
                        <input type="number" id="quantity" min="1" value="1" oninput="calculateTotal()">
                    </div>
                </div>
            `
        },
        bedcover: {
            html: `
                <div class="form-grid">
                    <div class="form-group">
                        <label>Ukuran Bed Cover</label>
                        <select id="type" onchange="calculateTotal()">
                            <option value="75000">Single Twin - Rp 75.000</option>
                            <option value="100000">Super Single/Double - Rp 100.000</option>
                            <option value="125000">Queen Size - Rp 125.000</option>
                            <option value="150000">King Size - Rp 150.000</option>
                            <option value="175000">Super King - Rp 175.000</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Jumlah (pcs)</label>
                        <input type="number" id="quantity" min="1" value="1" oninput="calculateTotal()">
                    </div>
                </div>
            `
        },
        sepatu: {
            html: `
                <div class="form-grid">
                    <div class="form-group">
                        <label>Jenis Sepatu</label>
                        <select id="type" onchange="calculateTotal()">
                            <option value="50000">Sports - Rp 50.000</option>
                            <option value="45000">Sneakers - Rp 45.000</option>
                            <option value="30000">Anak - Rp 30.000</option>
                            <option value="75000">Boots - Rp 75.000</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Jumlah (pcs)</label>
                        <input type="number" id="quantity" min="1" value="1" oninput="calculateTotal()">
                    </div>
                </div>
            `
        },
        karpet: {
            html: `
                <div class="form-grid">
                    <div class="form-group">
                        <label>Jenis Pembersihan</label>
                        <select id="type" onchange="calculateTotal()">
                            <option value="35000">Manual - Rp 35.000</option>
                            <option value="40000">Mesin - Rp 40.000</option>
                            <option value="50000">Steam - Rp 50.000</option>
                            <option value="75000">Dry Cleaning - Rp 75.000</option>
                            <option value="80000">Deep Cleaning - Rp 80.000</option>
                            <option value="85000">Masjid - Rp 85.000</option>
                            <option value="100000">Kantor - Rp 100.000</option>
                            <option value="150000">Express - Rp 150.000</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Jumlah (pcs)</label>
                        <input type="number" id="quantity" min="1" value="1" oninput="calculateTotal()">
                    </div>
                </div>
            `
        },
        boneka: {
            html: `
                <div class="form-grid">
                    <div class="form-group">
                        <label>Ukuran Boneka</label>
                        <select id="type" onchange="calculateTotal()">
                            <option value="35000">Kecil - Rp 35.000</option>
                            <option value="50000">Sedang - Rp 50.000</option>
                            <option value="50000">Besar - Rp 50.000</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Jumlah (pcs)</label>
                        <input type="number" id="quantity" min="1" value="1" oninput="calculateTotal()">
                    </div>
                </div>
            `
        },
        gorden: {
            html: `
                <div class="form-group">
                    <label>Total Harga</label>
                    <input type="number" id="manual-price" min="0" placeholder="0" oninput="calculateTotal()">
                    <small>Masukkan harga sesuai kesepakatan</small>
                </div>
            `
        },
        bantal: {
            html: `
                <div class="form-group">
                    <label>Total Harga</label>
                    <input type="number" id="manual-price" min="0" placeholder="0" oninput="calculateTotal()">
                    <small>Masukkan harga sesuai kesepakatan</small>
                </div>
            `
        }
    };

    container.innerHTML = serviceConfigs[currentService].html;
}

// ===== TRANSACTION FORM =====
function initializeTransactionForm() {
    const form = document.getElementById('transaction-form');
    form.addEventListener('submit', (e) => {
        e.preventDefault();
        saveTransaction();
    });

    const deliveryCheck = document.getElementById('delivery-check');
    deliveryCheck.addEventListener('change', () => {
        const deliveryInputs = document.getElementById('delivery-inputs');
        if (deliveryCheck.checked) {
            deliveryInputs.classList.remove('hidden');
        } else {
            deliveryInputs.classList.add('hidden');
            document.getElementById('delivery-distance').value = 0;
        }
        calculateTotal();
    });

    const deliveryDistance = document.getElementById('delivery-distance');
    deliveryDistance.addEventListener('input', calculateTotal);
}

function calculateTotal() {
    let total = 0;

    // Calculate base price based on service
    if (currentService === 'baju') {
        const weight = parseFloat(document.getElementById('weight')?.value) || 0;
        const pricePerKg = 10000;
        let subtotal = weight * pricePerKg;

        // Apply discount: 10% per 10kg multiple
        const multiple = Math.floor(weight / 10);
        const discountPercent = multiple * 10;
        const discount = subtotal * (discountPercent / 100);

        total = subtotal - discount;
    } else if (['selimut', 'bedcover', 'sepatu', 'karpet', 'boneka'].includes(currentService)) {
        const price = parseInt(document.getElementById('type')?.value) || 0;
        const quantity = parseInt(document.getElementById('quantity')?.value) || 0;
        total = price * quantity;
    } else {
        // Manual price for gorden and bantal
        total = parseInt(document.getElementById('manual-price')?.value) || 0;
    }

    // Add delivery fee if applicable
    if (document.getElementById('delivery-check').checked) {
        const distance = parseFloat(document.getElementById('delivery-distance').value) || 0;
        if (distance >= 5) {
            const extraKm = Math.ceil(distance - 5);
            const deliveryFee = 15000 + (5000 * extraKm);
            total += deliveryFee;
        }
    }

    document.getElementById('total-amount').textContent = formatRupiah(total);
    return total;
}

function saveTransaction() {
    const name = document.getElementById('customer-name').value;
    const method = document.getElementById('payment-method').value;
    const description = document.getElementById('description').value;
    const total = calculateTotal();

    if (!name || total <= 0) {
        alert('Mohon lengkapi data transaksi!');
        return;
    }

    const transaction = {
        id: nextTransactionId++,
        date: new Date().toLocaleString('id-ID'),
        name: name,
        service: currentService,
        description: description,
        method: method,
        status: 'Dalam Proses',
        total: total
    };

    transactions.unshift(transaction);
    historyStack.push(transaction.id);

    saveToLocalStorage();
    updateDashboard();
    renderHistory();
    resetTransactionForm();

    alert('✓ Transaksi berhasil disimpan!');
    switchPage('dashboard');
}

function resetTransactionForm() {
    document.getElementById('transaction-form').reset();
    document.getElementById('delivery-inputs').classList.add('hidden');
    renderServiceInputs();
    calculateTotal();
}

// ===== DASHBOARD =====
function updateDashboard() {
    // Calculate income by service
    const incomeBaju = transactions.filter(t => t.service === 'baju').reduce((sum, t) => sum + t.total, 0);
    const incomeSepatu = transactions.filter(t => t.service === 'sepatu').reduce((sum, t) => sum + t.total, 0);
    const incomeKarpet = transactions.filter(t => t.service === 'karpet').reduce((sum, t) => sum + t.total, 0);
    const totalIncome = transactions.reduce((sum, t) => sum + t.total, 0);

    document.getElementById('stat-baju').textContent = formatRupiah(incomeBaju);
    document.getElementById('stat-sepatu').textContent = formatRupiah(incomeSepatu);
    document.getElementById('stat-karpet').textContent = formatRupiah(incomeKarpet);
    document.getElementById('stat-total').textContent = formatRupiah(totalIncome);

    // Update recent transactions table
    const tbody = document.getElementById('recent-transactions');
    tbody.innerHTML = '';

    if (transactions.length === 0) {
        tbody.innerHTML = '<tr><td colspan="6" class="empty-state">Belum ada transaksi</td></tr>';
        return;
    }

    transactions.slice(0, 5).forEach(t => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>#${t.id}</td>
            <td>${t.name}</td>
            <td style="text-transform: capitalize">${t.service}</td>
            <td><span class="status-badge status-process">${t.status}</span></td>
            <td>${formatRupiah(t.total)}</td>
            <td>${t.date}</td>
        `;
        tbody.appendChild(row);
    });
}

// ===== HISTORY =====
function renderHistory() {
    const tbody = document.getElementById('history-table');
    const searchTerm = document.getElementById('search-input')?.value.toLowerCase() || '';

    tbody.innerHTML = '';

    const filtered = transactions.filter(t =>
        t.name.toLowerCase().includes(searchTerm) ||
        t.service.toLowerCase().includes(searchTerm) ||
        t.id.toString().includes(searchTerm)
    );

    if (filtered.length === 0) {
        tbody.innerHTML = '<tr><td colspan="9" class="empty-state">Tidak ada transaksi ditemukan</td></tr>';
        return;
    }

    filtered.forEach(t => {
        const row = document.createElement('tr');
        const statusClass = t.status === 'Dalam Proses' ? 'status-process' :
            t.status === 'Selesai' ? 'status-done' : 'status-taken';

        row.innerHTML = `
            <td>#${t.id}</td>
            <td>${t.date}</td>
            <td>${t.name}</td>
            <td style="text-transform: capitalize">${t.service}</td>
            <td>${t.description || '-'}</td>
            <td>${t.method}</td>
            <td><span class="status-badge ${statusClass}">${t.status}</span></td>
            <td>${formatRupiah(t.total)}</td>
            <td>
                <button class="btn-text" onclick="changeStatus(${t.id})">Ubah Status</button>
            </td>
        `;
        tbody.appendChild(row);
    });
}

function changeStatus(id) {
    const transaction = transactions.find(t => t.id === id);
    if (!transaction) return;

    const statuses = ['Dalam Proses', 'Selesai', 'Sudah Diambil'];
    const currentIndex = statuses.indexOf(transaction.status);
    const nextIndex = (currentIndex + 1) % statuses.length;

    transaction.status = statuses[nextIndex];

    saveToLocalStorage();
    renderHistory();
    updateDashboard();
}

function undoLastTransaction() {
    if (historyStack.length === 0) {
        alert('Tidak ada transaksi untuk dibatalkan!');
        return;
    }

    const lastId = historyStack.pop();
    transactions = transactions.filter(t => t.id !== lastId);

    saveToLocalStorage();
    updateDashboard();
    renderHistory();

    alert('✓ Transaksi terakhir berhasil dibatalkan!');
}

// Initialize search
document.addEventListener('DOMContentLoaded', () => {
    const searchInput = document.getElementById('search-input');
    if (searchInput) {
        searchInput.addEventListener('input', renderHistory);
    }
});

// ===== CUSTOMERS =====
function renderCustomers() {
    const grid = document.getElementById('customers-grid');
    grid.innerHTML = '';

    if (customers.length === 0) {
        grid.innerHTML = `
            <div class="empty-state-card">
                <i class="fas fa-users"></i>
                <p>Belum ada data pelanggan</p>
            </div>
        `;
        return;
    }

    customers.forEach(c => {
        const card = document.createElement('div');
        card.className = `customer-card ${c.isMember ? 'member' : ''}`;
        card.innerHTML = `
            <div style="display: flex; align-items: center; gap: 12px; margin-bottom: 16px;">
                <div class="avatar" style="width: 48px; height: 48px; font-size: 20px;">
                    ${c.name.charAt(0).toUpperCase()}
                </div>
                <div>
                    <h3 style="margin-bottom: 4px;">${c.name}</h3>
                    ${c.isMember ? '<p style="color: var(--primary-gold); font-size: 12px; font-weight: 600;">★ MEMBER</p>' : ''}
                </div>
            </div>
            <p style="color: var(--text-secondary); margin-bottom: 8px;">
                <i class="fas fa-phone" style="width: 20px;"></i> ${c.phone || '-'}
            </p>
            <p style="color: var(--text-secondary);">
                <i class="fas fa-map-marker-alt" style="width: 20px;"></i> ${c.address || '-'}
            </p>
        `;
        grid.appendChild(card);
    });
}

function openCustomerModal() {
    document.getElementById('customer-modal').classList.add('active');
}

function closeCustomerModal() {
    document.getElementById('customer-modal').classList.remove('active');
    document.getElementById('customer-form').reset();
}

document.getElementById('customer-form').addEventListener('submit', (e) => {
    e.preventDefault();

    const name = document.getElementById('new-customer-name').value;
    const phone = document.getElementById('new-customer-phone').value;
    const address = document.getElementById('new-customer-address').value;
    const isMember = document.getElementById('new-customer-member').checked;

    customers.push({
        id: Date.now(),
        name: name,
        phone: phone,
        address: address,
        isMember: isMember
    });

    saveToLocalStorage();
    renderCustomers();
    closeCustomerModal();

    alert('✓ Pelanggan berhasil ditambahkan!');
});

// ===== UTILITIES =====
function formatRupiah(number) {
    return new Intl.NumberFormat('id-ID', {
        style: 'currency',
        currency: 'IDR',
        minimumFractionDigits: 0
    }).format(number);
}

function updateCurrentDate() {
    const dateElement = document.getElementById('current-date');
    const options = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' };
    dateElement.textContent = new Date().toLocaleDateString('id-ID', options);
}

// ===== LOCAL STORAGE =====
function saveToLocalStorage() {
    localStorage.setItem('luxe_transactions', JSON.stringify(transactions));
    localStorage.setItem('luxe_customers', JSON.stringify(customers));
    localStorage.setItem('luxe_history_stack', JSON.stringify(historyStack));
    localStorage.setItem('luxe_next_id', nextTransactionId.toString());
}

function loadFromLocalStorage() {
    const savedTransactions = localStorage.getItem('luxe_transactions');
    const savedCustomers = localStorage.getItem('luxe_customers');
    const savedHistory = localStorage.getItem('luxe_history_stack');
    const savedNextId = localStorage.getItem('luxe_next_id');

    if (savedTransactions) transactions = JSON.parse(savedTransactions);
    if (savedCustomers) customers = JSON.parse(savedCustomers);
    if (savedHistory) historyStack = JSON.parse(savedHistory);
    if (savedNextId) nextTransactionId = parseInt(savedNextId);
}
