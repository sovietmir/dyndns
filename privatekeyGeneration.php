<?php
// Generate a 32-byte random string
$randomBytes = openssl_random_pseudo_bytes(32);

// Encode the random bytes in base64 format
$privateKey = base64_encode($randomBytes);

// Print the private key
echo $privateKey;
?>
