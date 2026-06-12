import axios from "axios";
import cookies from "react-cookies"

export const endpoints = {
    "categories": "/categories",
    "products": "/products"
};

export const authAPIs = () => {
    return axios.create({
        baseURL: `${process.env.REACT_APP_API_BASE_URL}/api/`,
        headers: {
            'Authorization': `Bearer ${cookies.load('token')}`
        }
    });
}

export default axios.create({
    baseURL: `${process.env.REACT_APP_API_BASE_URL}/api`
})