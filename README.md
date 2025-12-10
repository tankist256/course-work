# Computer Hardware Store Inventory

Command-line inventory manager for hardware components.

## Build
```sh
make
```
## Run
```sh
./bin/inventory help
```
## Usage

### List Items
```sh
# List all products
./bin/inventory list-products

# List all manufacturers
./bin/inventory list-manufacturers

# List all categories
./bin/inventory list-categories

# List products below stock threshold
./bin/inventory list-below --threshold 20
```

### Search and Filter
```sh
# Search products by model name (case-insensitive)
./bin/inventory search-model --substr "RTX"

# Sort products
./bin/inventory sort-products --by price
./bin/inventory sort-products --by price --desc
./bin/inventory sort-products --by score|power|stock|model

# Advanced query with filters
./bin/inventory query --min-price 200 --max-price 500 --sort price
./bin/inventory query --cat <CATEGORY_UUID> --min-score 8000
./bin/inventory query --man <MANUFACTURER_UUID> --iface "PCIe 4.0 x16"
```

### Add Items
```sh
# Add manufacturer (returns UUID)
./bin/inventory add-manufacturer --name "NVIDIA" --country "USA" --est-month 4 --est-year 1993 --website "https://nvidia.com" --warranty 36

# Add category (returns UUID)
./bin/inventory add-category --name "GPUs" --desc "Graphics cards"

# Add product (returns UUID)
./bin/inventory add-product --model "RTX 4080" --man <MANUFACTURER_UUID> --cat <CATEGORY_UUID> --sku "RTX4080" --price 999.99 --stock 50 --rel-month 1 --rel-year 2024 --score 9500 --power 320 --iface "PCIe 4.0 x16" --warranty 36

# Add accessory to product
./bin/inventory add-accessory --uuid <PRODUCT_UUID> --acc <ACCESSORY_UUID>
```

### Update Items
```sh
# Update product stock
./bin/inventory upd-stock --uuid <UUID> --stock 25

# Update product price
./bin/inventory upd-price --uuid <UUID> --price 899.99

# Update manufacturer
./bin/inventory upd-manufacturer --uuid <UUID> --name "New Name" --country "USA" --est-month 1 --est-year 2000 --website "https://example.com" --warranty 24
```

### Delete Items
```sh
# Delete product
./bin/inventory del-product --uuid <UUID>

# Delete manufacturer (only if no products associated)
./bin/inventory del-manufacturer --uuid <UUID>

# Delete category (only if no products associated)
./bin/inventory del-category --uuid <UUID>

# Remove accessory
./bin/inventory rm-accessory --uuid <PRODUCT_UUID> --acc <ACCESSORY_UUID>
```

### Other Commands
```sh
# List products in a category
./bin/inventory list-products-in-category --uuid <CATEGORY_UUID>

# List accessories for a product
./bin/inventory list-accessories --uuid <PRODUCT_UUID>
```

### Database Directory

By default the program uses the 'db' directory for storing data files. you can specify a custom directory in two ways hard and easy

**Hard** **using environment variable**
```sh
export INVENTORY_DB_DIR=/path/to/custom/db
./bin/inventory list-products
```

**Easy** **using command-line option**
```sh
./bin/inventory --db /path/to/custom/db list-products
```

The `--db` option must come before any command

### View Commands
```sh
./bin/inventory help
```